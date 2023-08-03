#include "../include/Server.hpp"

namespace ft
{

void	Server::cap(User * user, Command *  cmd) 
{
	(void) cmd;
	if (DEBUG)
		std::cout << "CAP WAS CALLED, BUT IS SILENTLY IGNORED\n";
}

}