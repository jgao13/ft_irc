#include "../include/Server.hpp"
#include "../include/Debug_ft_IRC.hpp"


namespace ft {

	void	Server::user(User * user, Command * cmd)
	{
		if (DEBUG)
		{
			std::cout << PURPLE << "*** COMMAND USER ***\nParams received: " << RESET;
			for (std::vector<std::string>::iterator it = cmd->arguments().begin(); it != cmd->arguments().end(); it++)
			{
				if (it != cmd->arguments().begin())
					std::cout << ", ";
				std::cout << *it;
			}
		}
		if (cmd->arguments()[0].empty())
				user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user)));
		else
		{
			user->setUsername(cmd->arguments()[0]);
			user->setFirstName(cmd->arguments()[1]);
		}
		if (DEBUG)
			print_User(user);
	}
}