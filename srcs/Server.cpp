#include "../include/Server.hpp"
#include "../include/Utils.hpp"

namespace ft
{
	Server::Server(char * port, std::string password) : _done(0), _epoll_fd(0), _server_fd(0), _password(password), _port(0)
	{
		char *ptr = NULL;
		errno = 0;
		_port = strtol(port, &ptr, 10);
		if (*ptr || errno != 0 || _port < 1024 || _port > 65535)
			throw (std::runtime_error("Invalid port (port must be within the range [1024, 65535])\n"));
		_network = new Network(_port);
		_server_fd = _network->getServerFd();
		_commands["CAP"] = &Server::cap;
		_commands["PASS"] = &Server::pass;
		_commands["JOIN"] = &Server::join;
		_commands["NICK"] = &Server::nick;
		_commands["PING"] = &Server::ping;
		_commands["MODE"] = &Server::mode;
		_commands["TOPIC"] = &Server::topic;
		_commands["USER"] = &Server::user;
		_commands["WHOIS"] = &Server::whois;
		_commands["INVITE"] = &Server::invite;
		_commands["PRIVMSG"] = &Server::privmsg;
		print_server();


		// socket_fd = _network.init_server_socket(_port);
	}

	Server::~Server()
	{
		delete (_network);
		// close(socket_fd);
		// close(epoll_fd);
	}

	void Server::addChannel(const std::string& channelName, Channel* channel)
	{
		_channels.insert(std::pair<std::string, Channel *>(channelName, channel));
    	//_channelList[channelName] = channel;
	}

	int	Server::accept_connexion() 
	{
		struct epoll_event event;
		struct sockaddr in_addr;
		socklen_t in_len;
		int infd;
		char hbuf[128], sbuf[128];

		in_len = sizeof in_addr;
		infd = accept (_server_fd, &in_addr, &in_len);
		if (infd == -1)
		{
			// throw(std::runtime_error("Accept failed from server side\n"));
			return (-1);
		}
		_userList[infd] = new User(infd, in_addr);

		// GET NAME INFO FONCTION PAS AUTORISE !!!
		// De toute facon cest que de l'affichage
		int s = getnameinfo (&in_addr, in_len,
						hbuf, sizeof hbuf,
						sbuf, sizeof sbuf,
						NI_NUMERICHOST | NI_NUMERICSERV);
		if (s == 0)
		{
			std::cout << "Accepted connection on descriptor " << infd
			<< "(host=" << hbuf << ", port = " << sbuf << ")" << std::endl;
		}
		// Je sais pas si il faut le mettre en non_blocking
		// s = _network->make_socket_non_blocking(infd);
		if (s == -1)
		{
			return (-1);
		}

		event.data.fd = infd;
		event.events = EPOLLIN | EPOLLET;
		s = epoll_ctl (_epoll_fd, EPOLL_CTL_ADD, infd, &event);
		if (s == -1)
		{
			return (-1);
			// throw(std::runtime_error("epoll_ctl a merdé\n"));
		}
		if (DEBUG)
			std::cout << GREEN << "ACCEPT FINISHED WITHOUT PROBLEM\n" << RESET;
		return (0);
	}

	int	Server::read_Event(int index)
	{
		int done = 0;

		while (1)
		{
			ssize_t count;
			char buf[512];

			count = read (events[index].data.fd, buf, sizeof buf);
			if (count == -1)
			{
				/* If errno == EAGAIN, that means we have read all
					data. So go back to the main loop. */
				if (errno != EAGAIN)
				{
				//   perror ("read");
					done = 1;
				}
				break;
			}
			else if (count == 0)
			{
				/* End of file. The remote has closed the
					connection. */
				done = 1;
				break;
			}

			/* Write the buffer to standard output */
			int s = write (1, buf, count);
			if (s == -1)
			{
				throw(std::runtime_error("write a merdé\n"));
			}
		}
		if (done)
		{
			std::cout << "Closed connection on descriptor " << events[index].data.fd
			<< std::endl;
			close (events[index].data.fd);
		}
		done = 0;
		return (0);
	}

	int	Server::init_epoll()
	{
		if (getServSockFd() == -1)
			throw (std::runtime_error("Init epoll failed because of wrong server socket fd\n"));
		struct epoll_event event;
		this->_epoll_fd = epoll_create1(0);
		if (_epoll_fd == -1)
			throw (std::runtime_error("Failed to create epoll file descriptor\n"));
		std::cout << "EPOLL_FD == " << _epoll_fd << std::endl;
		event.events = EPOLLIN;
		event.data.fd = _server_fd;
		if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _server_fd, &event))
			throw(std::runtime_error("epoll_ctl a merdé\n"));
		return (0);
	}
	
	int		Server::run_Server()
	{
		std::cout << ORANGE << "Polling for input...\n" << RESET;
		int event_count = epoll_wait(_epoll_fd, events, MAX_EVENTS, 60 * 3 * 1000);
		// if (DEBUG)
		// {
		// 	int j = 0;
		// 	for (int i = 0; events[i].events != 0; i++)
		// 		j++;
		// 	std::cout << SILVER << "EPOLL WAIT STUFF\n----------\n" << " MAXEVENT== "
		// 	<< MAX_EVENTS << ", NUMBER OF EVENTS == " << j << RESET << std::endl;
		// }
		std::cout << GREEN << "EVENT COUNT == " << event_count << RESET << "\n"; 
		if (event_count == -1)
			throw(std::runtime_error("epoll_wait a merdé\n"));
		for (int i = 0; i < event_count; i++)
		{
			std::cout << ORANGE << "Reading FILE DESCRIPTOR '" << events[i].data.fd << RESET << "'\n";
			if ((events[i].events & EPOLLERR) ||
				(events[i].events & EPOLLHUP) ||
					(!(events[i].events & EPOLLIN)))
			{
				/* An error has occured on this fd, or the socket is not
					ready for reading (why were we notified then?) */
				std::cerr << "Epoll error\n";

				close (events[i].data.fd);
				continue;
			}
			if (events[i].data.fd == _server_fd)
			{

				int ret = accept_connexion();
				if (ret == -1)
					std::cerr << "Connexion could not be accepted, some function f'ed up\n";
			}
			else
			{
				_done = 0;
				read_stuff_from_socket(i);
				if (_done)
				{
					//TO DO::: VIRER LE USER QUI A LE FD CORRESPONDANT DE TOUTES LES LISTES
					std::cout << "Closed connection on descriptor " << events[i].data.fd
					<< std::endl;
					/* Closing the descriptor will make epoll remove it
						from the set of descriptors which are monitored. */
					close (events[i].data.fd);
				}
				//fonction remove users
			}
			_done = 0;

		}

		/* ICI, faire clean exit*/
		// free (events);
 		// close (socket_fd);
		return (0);
		//   return EXIT_SUCCESS;
	}

	// Used to 
	void	Server::read_stuff_from_socket(int index)
	{
		ssize_t count;
		char buf[512] = {};

		count = recv (events[index].data.fd, buf, 512 ,0);
		if (DEBUG)
		{
			write_f_all(buf);
		}
		if (count == -1)
		{
			std::cerr << "Problem with recv, disconnecting User on fd[" << events[index].data.fd << "]\n";
			if (errno != EAGAIN && errno != EWOULDBLOCK)
			{
				// perror ("recv");
				_done = 1;
			}
			// break;
		}
		else if (count == 0) // Connection performed an orderly shutdown
		{
			std::cout << "Connection closed remotely on fd == " << events[index].data.fd << std::endl;
			disconnectUser(events[index].data.fd, "Connection closed remotely", false);
			_done = 1;
		}
		else
		{
			std::string buffer(buf);
			processMsgEvent(buffer, events[index].data.fd);
			std::string delimiter("\r\n");
			size_t position;
			// TOUTE CETTE BOUCLE SERT PLUS A RIEN
		// 	while ((position = buffer.find(delimiter)) != std::string::npos)
		// 	{
		// 		std::string message = buffer.substr(0, position);
		// 		buffer.erase(0, position + delimiter.length());
		// 		if (!message.length())
		// 			continue;

		// 		// commands.push_back(new Command(this, server, message));
		// 		else 
		// 		{
		// 			std::cout << SILVER << "MESSAGE RECU PAR LE SERVER: \n-----------\n" << RESET;
		// 			print_f_all(message);
		// 			std::cout << SILVER << "\n-------------\n" << RESET;
					
		// 			std::string		command;
		// 			command = message.substr(0, message.find_first_of("\r\n"));
		// 			// command_JOIN(command, _userList[events[index].data.fd]);
		// 			std::cout << "MESSAGE AVANT ERASE:" << message << std::endl;
		// 			message = message.erase(0, message.find_first_of("\r\n"));
		// 			std::cout << "MESSAGE apres ERASE:" << message << std::endl;
		// 			command = message.substr(0, message.find_first_of("\r\n"));
		// 			// command_JOIN(command, _userList[events[index].data.fd]);
		// 		}
		// 	}
		}
	}

	int				Server::getServSockFd() 
	{
		std::cout << "SERVER_SOCKET_FD == " << _network->getServerFd() << "\n";
		return (_network->getServerFd());
	}

	void			Server::initCreationTime()
	{
		time_t	tmpTime = time(NULL);
		struct tm * timeinfo = localtime(&tmpTime);
		_creationTime = asctime(timeinfo);
		// removes the \n at the end of the string
		if (_creationTime.size() > 0)
			_creationTime.erase(_creationTime.size() - 1, 1);
	}

	// Handles the gestion of a client message, which means :
	// 1. Splitting the message into its differents part (maybe not after all)
	// 2. Identifying the User at the origin of the message
	// 2bis. Completing the buffered message that was in the client structure
	// 3. Executing the actions/commands
	void			Server::processMsgEvent(std::string buffer, int user_fd)
	{
		std::string delimiter("\r\n");
		size_t position;
		std::cout << "Server::processMsgEvent user_fd == " << user_fd << "\n";
		while ((position = buffer.find(delimiter)) != std::string::npos)
		{
			std::string message;
			User *	user = getUserByFd(user_fd);
			if (DEBUG)
			{
				std::cout << GREEN << "\n*** | SERVER | ***\n" << RESET;
				std::cout << GREEN << "Server::processMsgEvent \nis processing the message: |"
				<< RESET << buffer << GREEN << "| send by the User |" << RESET << user->nickname()
				<< GREEN << "| with socketfd == " << RESET << user->getUserFd() << "\n";
			}
			if (!user)
				std::cerr << "Logical problem: user socket fd is not in the Userlist\n";
			if (!user->_buffer.empty())
			{
				message = user->_buffer;
				user->_buffer.clear();
			}
			message = buffer.substr(0, position);
			buffer.erase(0, position + delimiter.length());
			execCommand(user, message);
		}
	}
	
	// Exec command splits the whole message into a Command class
	void	Server::execCommand(User * user, std::string message) 
	{
		// Euh je sais plus ou est fait le check du msg vide;
		Command	cmd(message, this, user);
		// if (cmd.getCmd() == NULL)
		// 	return ;
		if (DEBUG) 
		{
			std::cout << GREEN << "\n*** | SERVER | ***\n" << RESET;
			std::cout << GREEN << "Server::execCommand\n"
			<< "msg received: " << SILVER << message << RESET << "\n";
			// cmd.print_command();
		}
		Command_List::iterator it = _commands.find(cmd.command());
		if (it == _commands.end()) 
		{
			std::cout << GREEN << "Server::execCommand could not find " << RESET
			<< cmd.command() << GREEN << " in the command list\n";
			user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_UNKNOWNCOMMAND, user, cmd.command())));
			return;
		}
		(this->*(it->second))(user, &cmd);
	}

	void			Server::disconnectUser(int userFd, std::string reason, bool isInvis)
	{
		struct epoll_event	ev = {};
		int ret = epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, userFd, &ev);
		if (ret < 0)
		{
			std::cout << "Could not delete event(epoll_ctl failed), reason == ";
			// std::cout << "ERRNO == " << errno << ", LETTER CODE == " << strerrorname_np(errno) << std::endl;
			return;
		}
		std::cout << "disconnecting " << userFd << std::endl;
		// A finir, mais en gros, il fait notifier tt le monde du channel
		// Virer le User de Users et de UsersFd
		// Virer de la liste de user du Channel
		//if (!isInvis)
			//disconnection_Notification(userFd, reason);
	}


	std::string		Server::password() const {return _password;}
	std::string		Server::name() const {return _serverName;}
	// bool			Server::isInRegistrationList() const (std::string username)
	// {
	// 	if (_registration_list.count(std::toUpper(username)))
	// 		return (true);
	// 	return (false);
	// }

	// User *			Server::getUserByFd(int ufd) const
	// {
	// for (std::map<int, User *>::iterator it = _user.begin(); it != users.end(); ++it)
	// 	if ((*it).second->getNickname() == nick)
	// 		return (*it).second;
	// return NULL;	}


}

	ft::User *	ft::Server::getUserByName(std::string const nickname) const
	{
		std::map<int, ft::User *>::const_iterator it = _userList.begin();
		while (it != _userList.end() && ft::strToUpper(it->second->nickname()) != ft::strToUpper(nickname))
			it++;
		if (it != _userList.end())
			return it->second;
		return (NULL);
	}

	ft::User *	ft::Server::getUserByFd(int ufd) const
	{
		std::map<int, User *>::const_iterator it = _userList.find(ufd);
		if (it == _userList.end())
			return NULL;
		else
			return it->second;
	}

 ft::Channel *  	ft::Server::getChannelByName(std::string const channelName) const
 {
 	std::map<std::string, ft::Channel *>::const_iterator it = _channels.find(channelName);
 	if (it == _channels.end())
 		return NULL;
 	else
 		return it->second;
 }

std::string		ft::Server::strToUpper(std::string str_target)
{
	std::string s(str_target);
	std::string::iterator current = s.begin();
	for (std::string::iterator it = str_target.begin(); it != str_target.end(); it++, current++)
		*current = toupper(*it);
	return s;
}


/////////////////////ajout du print
//mes ajout --> pas encore tester
	void	ft::Server::print_epoll_setup(void)
	{
		std::cout << "\nepoll fd: " << this->_epoll_fd << std::endl;
		std::cout << "epoll running " << this->_running << std::endl;
		std::cout << "epoll_event: " << " pas fait" << std::endl;
		std::cout << "epoll listen_list: ";
		for (int i = 0; i < this->listen_list.size(); i++)
		{
			if (i !=  0)
				std::cout << ", ";
			std::cout << this->listen_list[i];
		}
		std::cout << std::endl;
	}

	void	ft::Server::print_part4(void)
	{
		std::map<int, User*>::iterator begin = this->_userList.begin();
		std::map<int, User*>::iterator end = this->_userList.end();

		std::cout << "\n _userlist: ";
		while (begin != end)
		{
			std::cout << begin->first << " => " << begin->second << std::endl;
			begin++;
		}
		std::cout << "end of _userlist\n";
		std::cout << "_server_password: " << this->_password << std::endl;
		std::cout << "_serverName: " << this->_serverName << std::endl;

		
		std::map<std::string, Channel *>::iterator start = 	this->_channels.begin();
		std::map<std::string, Channel *>::iterator fin = 	this->_channels.end();
		std::cout << "channel list :\n";
		while (start != fin)
		{
			std::cout << start->first << " => " << start->second << std::endl;
			start++;
		}
		std::cout << "end of channel list\n";
		std::cout << "Channel list et Command_list a faire\n";

		std::cout << "_list_connected_users: ";
		for (int i = 0; i < this->_list_connected_users.size(); i++)
		{
			if (i != 0)
				std::cout << ", ";
			std::cout << this->_list_connected_users[i];
		}
		std::cout << std::endl;
	}
	void	ft::Server::print_server(void)
	{
		std::cout << PURPLE << "SERVER:\n----------\n";
		//print_epoll_setup();
		print_part4();
		std::cout << "\n-----END OF SERVER CHECK-------\n";
	}

	std::string ft::Server::getPassword(void)
	{
		return (_password);
	}
//////////////fin de l'ajout du print 


	// Create the socket, with the relevant options/flags, set it to non blocking
	// and binding it to an ip address, and listen...
	// I should split this function
	// int	Server::init_socket(unsigned int addrs)
	// {
	// 	// int	fd_serv;
	// 	//1. Socket Creation
	// 	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	// 	if (socket_fd == -1)
	// 	{
	// 		for (int i = 0; i < 4; i++)
	// 		{
	// 			socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	// 			if (socket_fd != -1)
	// 				break;
	// 		}
	// 		if (socket_fd == -1)
	// 			throw std::runtime_error(std::string("socket failed"));
	// 	}	

	// 	const int opt = 1;
	// 	int ret = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	// 	if (ret < 0)
	// 		throw std::runtime_error(std::string("setsockopt failed: ") + strerror(errno));
	// 	ret = fcntl(socket_fd, F_SETFL, O_NONBLOCK);
	// 	sockaddr_in my_addr;
	// 	if (ret != 0)
	// 		throw std::runtime_error(std::string("fcntl failed: ") + strerror(errno));
	// 	my_addr.sin_family = AF_INET;
	// 	my_addr.sin_port = htons(addrs);
	// 	//2. Bind (a proteger)
	// 	ret = bind(socket_fd, (struct sockaddr *) &my_addr, sizeof(sockaddr_in));
	// 	if (ret != 0)
	// 		throw std::runtime_error(std::string("bind failed: ") + strerror(errno));
	// 	//3. epoll Creation
	// 	// server.epoll_fd = epoll_create(0);
	// 	// if (server.epoll_fd == -1)
	// 	// {

	// 	// 	perror("epoll_create1");
	// 	// 	exit(EXIT_FAILURE);
	// 	// }
	// 	//4. listen mode, avec le nombre max de connections
	// 	const int backlog = 128;
	// 	ret = listen(socket_fd, backlog);
	// 	if (ret != 0)
	// 		throw std::runtime_error(std::string("listen failed: ") + strerror(errno));
	// 	// if (listen(server.socket_fd, 512) == -1)
	// 	// 	exit(EXIT_FAILURE);
	// 	return (ret);
	// }

	// int	Server::make_socket_non_blocking(int sfd)
	// {
	// 	int	flags, s;

	// 	flags = fcntl(sfd, F_GETFL, 0);
	// 	if (flags == -1)
	// 		throw(std::runtime_error("fcntl a merdé\n"));
		
	// 	s = fcntl (sfd, F_SETFL, flags);
	// 	if (s == -1)
	// 		throw(std::runtime_error("fcntl a merdé\n"));
	// 	return (0);
	// }

/* EXPLICATIONS */


		/* ******************************************************************** */
		/* ********************** PARTIE 1: SOCKET ACTION ********************* */
		/* ******************************************************************** */
