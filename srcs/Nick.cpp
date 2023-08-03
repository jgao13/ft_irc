#include "../include/Server.hpp"

namespace ft
{
	void	Server::nick(User * user, Command * cmd)
	{
		user->setNickname(cmd->arguments()[0]);
		std::cout << "command nick starting\n" << cmd->arguments()[0] << "  " << std::endl;
		if (DEBUG)
		{
			// print_command(cmd);
		}
	}
}