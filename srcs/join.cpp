#include "../include/Server.hpp"

namespace ft
{

	//If join with nothing, silently ignore it pls
	void	Server::join(User *user, Command * cmd)
	{

		// if (!isAlreadyConnected(user))
		// {
			user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user)));

			user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, user)));
			return;
			// FAUDRA RENVOYER UN MSG AU CLIENT COMME QUOI IL A PAS LE PASS
		// }
	}
}