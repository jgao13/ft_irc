#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <vector>
#include <string>
#include <iostream>
#include "../include/Utils.hpp"
#include "../include/Server.hpp"
#include "../include/User.hpp"

#ifndef DEBUG
#define DEBUG 0
#endif

/*
	This class is used to parse the message, splitting it into 3 components: 
	COMMAND, ARGUMENTS, MESSAGE
	(it is mainly a parser, with some checks done and the respective error reply if 
	it doesn't pass the checks)
	An IRC message must be in the format <><><>

*/
namespace ft
{
	class	Server;
	class	User;
	class	Command
	{
		public:
			Command(std::string message, Server * server, User * user);
			~Command();

			std::vector<std::string>	arguments() const;
			std::string					command() const;
			std::string					message() const;
			// DEBUG
			void						print_command(void);

			// std::vector<str::string>	arguments() const;
		private:
			Command();
			std::string					_command;
			std::vector<std::string>	_arguments;
			std::string					_message;
			std::string					_prefix;
			Server *					_server;
			User *						_user;
			bool	_error;

			int		parse_message(std::string msg);
	};
}


#endif