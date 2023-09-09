#pragma once

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>					// pour fcntl
#include <stdexcept>
#include <cerrno>
#include <string.h>
#include <netinet/in.h>				// pour struc sockaddr_in
#include <sys/epoll.h>				// pour epoll
#include <iostream>					// 
#include <vector>
#include <netdb.h>					// getaddrinfo
#include <stdlib.h>
#include <map>
#include <cstring>					//strchr
#include "../include/Colors.hpp"
#include "../include/Utils.hpp"
#include "../include/Command.hpp"
#include "User.hpp"
//#include "Nick.hpp"
#include "Network.hpp"
#include "Message_Format.hpp"
#include "../include/Debug_ft_IRC.hpp"

//Ca ptetre a virer
#include "cmd_err_replies.hpp"
#include "cmd_replies.hpp"

// DEBUG
#include <fstream>


#ifndef DEBUG
#define DEBUG 0
#endif

# define MAX_EVENTS 128

/*
	Le serveur est composé de 2(3?) gros blocs:
		1. La partie socket, qui crée le socket (init()), start() et accept()
		2. La partie epoll, qui gere le epoll, les messages et les connexions
		avec les clients (relié a la partie socket), qui va surement gerer les
		messages ?
		3. La partie commande qui va gérer la structure interne des channels
		et des users et va renvoyer les reponses avec les clients

		La flemme de split la classe en sous classe d'heritage, je veux juste
		que ca tourne
*/

namespace ft
{
	class User;

	class Channel;

	class Network;

	class Command;
	
	class Server
	{
		// Each COMMAND have the same 2 arguments: the User doing the command and a string table
		typedef	std::map<std::string, void	(Server::*) (User *, Command *)>	Command_List;
		typedef std::map<int, User *>				UserSocketList;
		typedef	std::map<std::string, User *>		UserList;
		typedef std::map<std::string, Channel *>	ChannelList;


		public:
			Server(char * port, std::string password);
			~Server();
			void	print_epoll_setup(void);
			void	print_part4(void);
			void	print_server(void);

		/*		PARTIE 1: SOCKET CREATION, CONFIGURATION AND HANDLING		*/
		private:
			Network *			_network;	// c'est lui qui gère toute la partie socket
			long int			_port;
			int					_server_fd;	// no comment
			std::string			_password;

		/*		PARTIE 2: 			EPOLL SETUP								*/
		private:
			int					_epoll_fd;
			int					_running;
			epoll_event			events[MAX_EVENTS];
			// std::vector<epoll_event>	events;
			std::vector<int>	listen_list;

		public:
			// Functions
			int					init_epoll();
			void				read_stuff_from_socket(int index);

			static struct 		epoll_event _ev;

		/*		PARTIE 3:			SERVER RUNNING							*/
		public:
			int					run_Server();
			int					read_Event(int index);
		
		private:
			// Functions
			int					accept_connexion();	// accept first connection request on the queue and return fd
			// Attributes
			bool				_done;

		/*		PARTIE 4:			??????									*/
		private:	
			void				initCreationTime();
			void				processMsgEvent(std::string buffer, int user_fd);
			void				execute_message(std::string message, User * user);
			void				disconnectUser(int userFd, std::string reason, bool isInvis);

			std::map<int, User *>			_userList;
			std::string						_server_password;
			std::string						_serverName;
			std::map<std::string, Channel>	_channelList;
			Command_List					_commands;
			std::vector<std::string>		_list_connected_users;

		public:

			std::string			name() const;
			std::string			password() const;

			int					getServSockFd();
			void				execCommand(User * user, std::string message);

			std::string			getPassword(void);
			// void				command_JOIN(std::string params, User *someone);
			User *				getUserByFd(int sfd) const;
			User *				getUserByName(std::string const nickname) const;
			Channel *			getChannelByName(std::string const channelName) const;
			std::string			strToUpper(std::string const str_target);
			// bool				isInRegistrationList(std::string) const;
			// On a besoin de lui pour 
			std::string			server_MsgFormat(std::string content);
			std::string			_creationTime;

			/* COMMANDS*/
			void	cap(User * user, Command *  cmd);
			void	join(User * user, Command *  cmd);
			void	pass(User * user, Command *  cmd);
			void	nick(User * user, Command *  cmd);
			void	user(User * user, Command *  cmd);
			void	kick(User * user, Command * cmd); // pas encore tester / rajouter le channel ?
			void	invite(User * user, Command *cmd);



			/* DEBUG */
			// void	clearFd() {close(socket_fd); close(epoll_fd);}
	};


}
