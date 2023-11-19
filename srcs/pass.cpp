#include "../include/Server.hpp"

namespace ft
{
	
//ma tentative de commande pass :
	void Server::pass(User *user, Command *cmd)
	{
		std::string password = cmd->arguments()[0];
		if (user->printStatus() == "REGISTER")
		{
			user->sendMsg("462 ERR_ALREADYREGISTERED :You're already registered\r\n");
			//std::cout << 462 << std::endl; //message d'erreur already register
			return ;
		}
		if (user->printStatus() == "ONLINE")
		{
			user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_ALREADYREGISTRED, user)));
			return;
		}
		if (password.empty())
		{
			user->sendMsg("461 ERR_NEEDMOREPARAMS :Not enough parameters\r\n");
			//std::cout << 461 << std::endl; //pas assez de parametre
			return ;
		}
		else
			{
				//std::cout << "pass envoyer :" << password << " pass du server : " << getPassword() << "\n\n\n\n";
				if (password == getPassword())
				{
					user->setStatus(User::REGISTER);
					std::cout << "Pass user fd == " << user->getUserFd() << "\n";
					// user->sendMsg("001 RPL_WELCOME :Welcome to the IRC server\r\n");
					//std::cout << "c pas elle\n";
					
					//std::cout << 001 << std::endl; //message de confirmation
					return ;
				}
				else
				{
					user->sendMsg("464 ERR_PASSWDMISMATCH :Password incorrect\r\n");
					//std::cout << 464 << std::endl; //incorrect password
					return ;
				}
			}
	}

}