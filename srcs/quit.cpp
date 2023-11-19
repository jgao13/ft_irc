#include "../include/Server.hpp"

namespace	ft
{
	void	Server::quit(User* user, Command * cmd)
	{
		if (user->printStatus() != "ONLINE")
		{
			user->sendMsg("ERROR : closing connection\r\n");
			disconnectUser(user->getUserFd(), cmd->argument(), false);
		}

		std::string reason = cmd->arguments()[0];
		for (Server::channel_iterator it = _channels.begin(); it != _channels.end(); it++)
		{
			Channel * channel = getChannelByName(it->first.c_str());
			if (!channel)
				user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NOSUCHCHANNEL, user)));
			else if (channel && !user->getChannelByName(channel->getName()))
				user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NOTONCHANNEL, user)));
			else
			{
				// Depending on implementation policy
				if (channel->isOperator(user))
					channel->removeOperator(user);
				channel->removeUser(user);
				if (channel->getNumberOfCurrentUser() == 0)
					this->removeChannel(channel->getName());
			}
		}
	}
}