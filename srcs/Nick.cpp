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
		std::cout << "Invalide char check\n\n";
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
		std::string nick = cmd->arguments()[0];
		if (nick.empty())
			std::cout << 431 << std::endl;
		else if (nick.size() > 9 || !invalideChar(nick))
			std::cout << 432 << std::endl;
		//else if(verifier la liste de tous les pseudo mais je sais pas ou ils sont stocker dans le channel)
			//{occurence trouver return erreur 433}
		else
		{
			//print old NICK new (source chat gpt tu connais)
			std::cout << user->getNickname() << " NICK " << nick << std::endl; 
			user->setNickname(nick);

		}
		if (DEBUG)
		{
			// print_command(cmd);
		}
	}
}