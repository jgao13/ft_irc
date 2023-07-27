#include "../include/Server.hpp"

namespace ft {

	void	Server::user(User * user, std::vector<std::string> params)
	{
		if (DEBUG)
		{
			std::cout << PURPLE << "*** COMMAND USER ***\nParams received: " << RESET;
			for (std::vector<std::string>::iterator it = params.begin(); it != params.end(); it++)
			{
				if (it != params.begin())
					std::cout << ", ";
				std::cout << *it;
			}
		}
		if (params[0].empty())
				user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user)));
		else
		{
			user->setUsername(params[0]);
			user->setFirstName(params[1]);
		}
		// if (DEBUG)
			// print_User(user);
	}
}