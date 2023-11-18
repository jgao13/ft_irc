#include "../include/Server.hpp"

namespace ft
{
	void	Server::ping(User * user, Command * cmd)
	{
		// time_t begin = time( NULL );
		user->sendMsg(serverMessageBuilder(this, "PONG " + _serverName + " " + cmd->arguments()[0]));
// 		user->send(serverMessageBuilder(*this, commandMessageBuilder(CODE_ERR_ALREADYREGISTRED, user)));
	}
}