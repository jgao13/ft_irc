#include "../include/Server.hpp"

namespace	ft
{
	void	Server::quit(User* user, Command * cmd)
	{
		if (user->printStatus() == "PASSWORD")
		{
			// user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, user)));

			// user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_PASSWDMISMATCH, user)));
			return;
		}
		if (user->printStatus() == "REGISTER")
		{
			// user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NOTREGISTERED, user)));
			return;
		}
		if (cmd->arguments().size() < 1) 
		{
			user->sendMsg("461 ERR_NEEDMOREPARAMS :Not enough parameters\r\n");
			return;
		}

		std::string channelName = cmd->arguments()[0];
		std::vector<std::string> channels = split(channelName, ",");
		for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
		{
			Channel * channel = getChannelByName(*it);
			if (!channel)
				user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NOSUCHCHANNEL, user)));
			else if (channel && !user->getChannelByName(channel->getName()))
				user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NOTONCHANNEL, user)));
			else
			{
				// Depending on implementation policy
				// if (channel->isOperator(user))
				// 	channel->removeOperator(user);
				channel->removeUser(user);
				if (channel->getNumberOfCurrentUser() != 0)
				{
					std::string message = user->getNickname() + " is leaving the channel" + channel->getName();
					if (cmd->arguments().size() == 2)
						message += " with reason: " + cmd->arguments()[1];
					channel->sendMessageToMembers(message);
				}
				else
					this->removeChannel(channel->getName());
			}
		}
	}
}