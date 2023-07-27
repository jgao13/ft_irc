#include "../include/Server.hpp"

namespace ft
{
	void	Server::pass(User * user, Command * cmd)
	{
		if ((cmd->arguments().size() == 1 && cmd->arguments()[0] == password()) || password().empty())
		{
			// Euh, la jai buggé sur la syntaxe
			
			user->setStatus(User::REGISTER);
			return;
		}
		if (cmd->arguments().empty())
		{
			user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user, "PASS")));
			return;
		}
		// else
		// {
		// 	user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_PASSWDMISMATCH, user)));
		// 	disconnect(user, "Wrong Password");
		// 	return;
		// }

	}

}