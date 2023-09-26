#pragma once
#include <netinet/in.h>
#include <sys/socket.h>		// for inet_ntoa
#include <netinet/in.h>		// for inet_ntoa
#include <arpa/inet.h>		// for inet_ntoa
#include <set>
#include "Server.hpp"
#include "Channel.hpp"
#ifndef DEBUG
#define DEBUG 0
#endif
#ifndef CRLF
#define CRLF "\r\n"
#endif
/*				**** USER.HPP ****
	1. Brief Description
This class must be able to correctly handle his own creation, initializing his
own socket, save all the correct information, and have flags to check availability
and requirements.
The User is created by the epoll handler, when it tries to connect.

	2. Attributes:
	std::string							_username;
	std::string							_nickname;
	std::string							_realname;
	std::string							_awayMessage;
	UserRequirement						_requirements;
	UserMode							_mode;
	unsigned int						_channelCount;
	std::set<Channel *>					_channelList;
	int									_socketfd;
	std::string							_buffer;
	std::string							_hostname;
	bool								_quit;
	int ou uint32						_flags; (ici, soit 2 flags, un
	pour requirement et lautre pour mode, avec leur getter et setter)

	3. List of flags:
	Not in order:
	REQUIREMENTS
					PASS
					NICK
					USERNAME
					SKIP_PASS
					ALL
	MODE
					ERROR
					AWAY
					INVISIBLE
					RESTRICTED
					OPERATOR
					WALLOPS (maybe not this one)

	4. Step by step.
		1) User(int socket fd, int requirementFlags)
		2) Configure the socket
			2a) set _hostname with inet_ntoa
		3) set requirement in requirementFlags
			3a) set channelCount to 0, in case user can be in more than 1 channel



*/

namespace ft
{
	class Server;

	class Channel;

	class User
	{
		public:
			enum Status
			{
				PASSWORD = 0,
				REGISTER = 1,
				ONLINE = 1 << 1
			};
			enum USERMode {
				ERROR = 0,
				AWAY = 1,
				INVISIBLE = 1 << 1,
				RESTRICTED = 1 << 2,
				OPERATOR = 1 << 3,
				WALLOPS = 1 << 4
			};
			User(int fd, sockaddr address);
			~User();
			//void		setPassword(std::string pass) {_password = pass;}
			//std::string	getPassword(void) {return _password;}
			void		setNickname(std::string nick);
			void		setFirstName(std::string fname);
			void		setStatus(User::Status status);
			void		setUsername(std::string	username);
			std::string nickname(void) const;
			std::string username(void) const;
			std::string	hostname(void) const;
			int			userfd(void) const;
			std::string						_buffer;
			void			sendMsg(std::string content);
			//bool			isRegistered() const;

			/* GETTERS AND SETTERS */
			int			getUserFd();
			std::string	getUsername();
			std::string	getNickname();
			std::string	getFirstName();
			std::string	getLastName();
			std::string	printStatus();

			//channel
    		bool isInvitedTo(const std::string& channelName) const;
    		void joinChannel(Channel* channel);

			



		private:
			// int								_sfd; 				// stands for socket fd
			int								_userfd;
			User() {};
			bool							_isServerOperator;
			std::set<Channel *> 			_channelList;
			std::string						_username;
			std::string						_nickname;
			std::string						_first_name;
			std::string						_last_name;
			std::string						_awayMessage;
			Status							_status;

			int								_requirements;
			int								_mode;
			unsigned int					_channelCount;
			std::string						_hostname;
			bool							_quit;
			int								_flags;
			sockaddr						_useraddress;

			std::set<std::string> _invitedChannels;
    		std::map<std::string, Channel*> _channels;

	};


}
