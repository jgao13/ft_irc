#include "../include/Server.hpp"


/*
	erreur : 
		- ERR_NONICKNAMEGIVEN 431 : pas de pseudo fourni
		- ERR_ERRONEUSNICKNAME 432 : pseudo non valide (caractere speciaux, pseudo trop long)
		- ERR_NICKNAMEINUSE (433) : pseudo deja utiliser dans le canal de discussion
		- ERR_UNAVAILRESOURCE (437) : plus de place
	succes :
		- execute et pseudo accepter -> envoyer une confirmation du changement de pseudo
*/
namespace ft
{
	bool	invalideChar(std::string nickname)
	{
		const char *valid_char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-"; //source chatgpt
		for (int i = 0; i < nickname.length(); i++)
		{
			if (!std::strchr(valid_char, nickname[i]))
			{
				std::cout << "PRINT A ENLEVER MAIS ON A TROUVER UN MAUVAIS CHAR DANS NICK\n";
				return false;
			}
		}
		return true;
	}

	void	Server::nick(User * user, Command * cmd)
	{
		//std::cout << "on est rentrer dans la commande nick \n\n\n\n\n\n\n\n";
		if (user->printStatus() == "PASSWORD")
		{
			user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user)));
			// user->_buffer.clear();
			return;
		}
		std::string nick = cmd->arguments()[0];
		if (nick.empty())
		{
			user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(431, user)));
			return ;
		}
		else if (nick.size() > 9 || !invalideChar(nick))
		{
			user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(432, user)));
			return ;
		}
		else
		{
			std::map<int, User *>::iterator it;
		for (it = _userList.begin(); it != _userList.end(); it++)
		{
			std::cout << "USERLIST :" << it->second->getNickname() << "\n";
			if (nick == it->second->getNickname())
			{
				user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(432, user)));
				std::cout << "c le meme pseudo\n\n";
				return ;
			}

		}
		}

			user->sendMsg("TA BIEN CHANGER DE PSEUDO FDP\r\n"); 
			user->setNickname(nick);

		if (DEBUG)
		{
			// print_command(cmd);
		}
	}
}