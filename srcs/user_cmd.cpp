#include "../include/Server.hpp"
#include "../include/Debug_ft_IRC.hpp"


namespace ft 
{
	void Server::user(User * user, Command * cmd)
	{
		if (user->printStatus() == "PASSWORD")
		{
			user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_PASSWDMISMATCH, user)));
			// user->_buffer.clear();
			return;
		}
	
		if (user->printStatus() == "ONLINE")
		{
			user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_ALREADYREGISTRED, user)));
			return;
		}

		if (cmd->arguments().size() < 4 || cmd->arguments()[0].empty()) {
			user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user)));
			return;
		}

		std::string username = cmd->arguments()[0];
		std::string realname = cmd->arguments()[3];

		// If Ident Protocol is not used or verification failed, prefix with '~'
		// Assume a function checkIdentProtocol(username) that returns true if verified
		while (checkRegistratedUser(username)) 
		{
			username = "~" + username;
			if (username.find("~~~") == 0)
			{
				user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user)));
				return;
			}


		}

		// USERNAME CHARACTER LIMIT == 12 (because IDK)
		if (username.length() > 12) {
			username = username.substr(0, 12);
		}
		while (checkRegistratedUser(username)) 
		{
			username = "~" + username;
			if (username.find("~~~") == 0)
			{
				user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user)));
				return;
			}
		}

		user->setUsername(username);
		user->setFirstName(realname);
		_registrated_users.push_back(username);
		if (!user->getNickname().empty())
		{
			user->setStatus(User::ONLINE);
			user->sendMsg(user->getClient() + " :" + RPL_WELCOME(user->getNickname())); // NR 001
			user->sendMsg(user->getClient() + " :" + RPL_YOURHOST(getServerName(), getVersion())); // NR 002
			user->sendMsg(user->getClient() + " :" + RPL_CREATED(getCreationTime())); // NR 003
			user->sendMsg(user->getClient() + RPL_MYINFO(getServerName(), VERSION, USER_MODES, CHAN_MODES)); // NR 004
		}
	}

}
