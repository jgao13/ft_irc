#include "../include/User.hpp"


namespace ft
{
	User::User(int fd, sockaddr address) : _userfd(fd), _useraddress(address), _flags(0), _status(PASSWORD)
	{
		if (DEBUG)
		{
			std::cout << BLUE << "\n------------\n" << "USER CREATION INFO:\n-----------\n"
			<< DEEPSKYBLUE << "_USERFD == " << RESET << _userfd << "\n"
			<< DEEPSKYBLUE << "_FIRST_NAME == " << RESET << _first_name << "\n"
			<< DEEPSKYBLUE << "_LAST_NAME == " << RESET << _last_name << "\n"
			<< DEEPSKYBLUE << "_ADDRESS == " << RESET;
			struct sockaddr_in *addrin = (struct sockaddr_in *)&address;
			std::cout << inet_ntoa(addrin->sin_addr) << ":" << ntohs(addrin->sin_port) 
			<< "\n---------\n";

			// for (int i = 0; _useraddress.sa_data)
		}
		// _userfd = socket(AF_INET, SOCK_STREAM, 0);
		// if (_socket = -1)
		// 	throw (std::runtime_error(std::string("Problem configuring new user")));
	}

	void	User::sendMsg(std::string message)
	{
		const char *	data = message.c_str();
		size_t			length = message.size();
		std::size_t	sent = 0;
		while (sent < length)
		{
			long int ret = ::send(_userfd, data + sent, length - sent, MSG_NOSIGNAL);
			if (ret == -1) {
				if (errno == EAGAIN || errno == EWOULDBLOCK)
					continue;
				else
					throw std::runtime_error(std::string("send error: ") + strerror(errno));
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
};