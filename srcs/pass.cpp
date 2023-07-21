#include "../include/Server.hpp"

namespace ft
{
	void	Server::pass(User * user, std::vector<std::string> params)
	{
		if ((params.size() == 1 && params[0] == password()) || password().empty())
		{
			// Euh, la jai buggé sur la syntaxe
			
			user->setStatus(User::REGISTER);
			return;
		}
		if (params.empty())
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