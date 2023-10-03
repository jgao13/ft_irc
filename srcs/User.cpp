#include "../include/User.hpp"


namespace ft
{
	// User::User(int fd, sockaddr address) : _userfd(fd), _useraddress(address), _flags(0), _status(PASSWORD)
	// {
	// 	// if (DEBUG)
	// 	// {
	// 	// 	std::cout << BLUE << "\n------------\n" << "USER CREATION INFO:\n-----------\n"
	// 	// 	<< DEEPSKYBLUE << "_USERFD == " << RESET << _userfd << "\n"
	// 	// 	<< DEEPSKYBLUE << "_FIRST_NAME == " << RESET << _first_name << "\n"
	// 	// 	<< DEEPSKYBLUE << "_LAST_NAME == " << RESET << _last_name << "\n"
	// 	// 	<< DEEPSKYBLUE << "_ADDRESS == " << RESET;
	// 	// 	struct sockaddr_in *addrin = (struct sockaddr_in *)&address;
	// 	// 	std::cout << inet_ntoa(addrin->sin_addr) << ":" << ntohs(addrin->sin_port) 
	// 	// 	<< "\n---------\n";

	// 	// 	// for (int i = 0; _useraddress.sa_data)
	// 	// }
	 	//_userfd = socket(AF_INET, SOCK_STREAM, 0);
	// 	//if (_socket = -1)
	// 	//	throw (std::runtime_error(std::string("Problem configuring new user")));
	// }

	User::User(int fd, sockaddr address)
	{	
		_userfd = fd;	
		// _userfd = socket(AF_INET, SOCK_STREAM, 0);
		_isServerOperator = false;


		_status = PASSWORD;

		_requirements = 0;
		_mode = 0;
		_channelCount = 0;

		_quit = false;
		_flags = 0;
		_useraddress = address;

	}

	void	User::sendMsg(std::string message)
	{
		const char *	data = message.c_str();
		size_t			length = message.size();
		//std::cout << data << "length : " << length<< std::endl;
		std::size_t	sent = 0;
							std::cout << "User::sendMsg user fd == " << this->getUserFd() << "\n";

		while (sent < length)
		{
			// ok le - 1 que j'ai rajouter sauve le truc donc il y a un probleme genre le _userfd change
			long int ret = ::send(_userfd /*- 1*/, data + sent, length - sent, MSG_NOSIGNAL);
			// std::cout << "ret dans send msg :" << ret << std::endl;
			std::cout << "userfd dans send msg :" << _userfd << std::endl;
			// std::cout << "data + length dans send msg :" << data + length << std::endl;
			// std::cout << "length - sent :" << length - sent << std::endl;
			// std::cout << "MSG_NOSIGNQL dans send msg :" << MSG_NOSIGNAL << std::endl;
			
			if (ret == -1) {
				if (errno == EAGAIN || errno == EWOULDBLOCK)
					continue;
				else
				{
					//std::cout << "l'erreur envoyer : " << strerror(errno)<< std::endl;
					throw std::runtime_error(std::string("send error: ") + strerror(errno));
				}
			}
			sent += ret;
			if (DEBUG)
			{
				std::cout << CYAN << "*** | USER | ***\n" << RESET;
				std::cout << CYAN << "USER::SEND is trying to send : " << RESET;
				print_f_all(data);
				std::cout << CYAN <<"\nwith ret == " << ret << RESET <<"\n";
			}
		}
	}

	User::~User() { } // ptetre close fd ici ?

	void		User::setNickname(std::string nick) 	{_nickname = nick;}
	void		User::setFirstName(std::string fname) 	{_first_name = fname;}
	void		User::setStatus(User::Status status)	{_status = status;}
	void		User::setUsername(std::string username)	{_username = username;}
	int			User::getUserFd()						{return _userfd;}
	std::string	User::getUsername()						{return _username;}
	std::string	User::getNickname()						{return _nickname;}
	std::string	User::getFirstName()					{return _first_name;}
	std::string	User::getLastName()						{return _last_name;}
	std::string	User::printStatus()						
	{switch (_status)
		{
		case 0:
			return "PASSWORD";

		case 1:
			return "REGISTER";

		case 1 << 1:
			return "ONLINE";
		
		default:
			return "ERROR";
		}
	}

	std::string User::nickname() const 					{return _nickname;}
	std::string	User::username() const					{return _username;}
	std::string	User::hostname() const					{return _hostname;}
	int			User::userfd() const 					{return _userfd;}
	//bool		User::isRegistered() const				{return (_status<<0)}

	bool User::isInvitedTo(const std::string& channelName) const {
    // Vérifie si l'utilisateur a été invité dans le canal spécifié
    return _invitedChannels.find(channelName) != _invitedChannels.end();
}

void User::joinChannel(Channel* channel) {
    // Ajoute l'utilisateur au canal
    _channels[channel->getName()] = channel;
    // Vous pouvez également effectuer d'autres actions ici, comme l'ajout de l'utilisateur aux opérateurs, etc.
}

Channel* User::getCurrentChannel(User* user) {
	std::map<std::string, Channel *>::iterator it = _channels.begin();
	std::map<std::string, Channel *>::iterator last = _channels.end();
    // Parcourez la liste des canaux pour trouver celui où l'utilisateur est membre
    while (it != last)
	{
        Channel* channel = it->second;
        if (channel->isUserMember(user)) {
            return channel;
			it++;
        }
    }
    return NULL;
}
};