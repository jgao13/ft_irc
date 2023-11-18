#include "../include/Server.hpp"
#include "../include/Debug_ft_IRC.hpp"


namespace ft {

	void	Server::user(User * user, Command * cmd)
	{
		if (user->printStatus() == "PASSWORD")
		{
			
			user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_PASSWDMISMATCH, user)));
			// user->_buffer.clear();
			return;
		}
		if (cmd->arguments()[0].empty())
				user->sendMsg(serverMessageBuilder(this, commandMessageBuilder(CODE_ERR_NEEDMOREPARAMS, user)));
		else
		{
			user->setUsername(cmd->arguments()[0]);
			user->setFirstName(cmd->arguments()[1]);
		}

		if (DEBUG)
			print_User(user);
	}
}