#include "../include/Server.hpp"

namespace ft
{

void	Server::cap(User * user, std::vector<std::string> params) 
{
	(void)user;
	(void)params;
	if (DEBUG)
		std::cout << "CAP WAS CALLED, BUT IS SILENTLY IGNORED\n";
}
}