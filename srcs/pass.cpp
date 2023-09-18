#include "../include/Server.hpp"

namespace ft
{
	
//ma tentative de commande pass :
	void Server::pass(User *user, Command *cmd)
	{
		std::string password = cmd->arguments()[0];
		if (user->printStatus() == "REGISTER")
		{
			std::cout << 462 << std::endl; //message d'erreur already register
			return ;
		}
		if (password.empty())
		{
			std::cout << 461 << std::endl; //pas assez de parametre
			return ;
		}
		else
			{
				if (password == getPassword())
				{
					user->setStatus(User::REGISTER);
					std::cout << 001 << std::endl; //message de confirmation
					return ;
				}
				else
				{
					std::cout << 464 << std::endl; //incorrect password
					return ;
				}
			}
	}

}