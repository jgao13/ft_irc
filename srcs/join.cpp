#include "../include/Server.hpp"

namespace ft
{

	//If join with nothing, silently ignore it pls
void	Server::join(User *user, std::vector<std::string> params)
{

	// if (!isAlreadyConnected(user))
	// {
		user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, user)));
		return;
	// }
}
}