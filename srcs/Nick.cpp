#include "../include/Server.hpp"

namespace ft
{
	void	Server::nick(User * user, std::vector<std::string> params)
	{
		user->setNickname(params[0]);
		std::cout << "command nick starting\n" << params[0] << "  " << std::endl;
	}
}