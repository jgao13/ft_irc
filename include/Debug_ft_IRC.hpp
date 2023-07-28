#ifndef DEBUG_FT_IRC
# define DEBUG_FT_IRC

# include <string>
# include "Colors.hpp"
# include "Command.hpp"
# include "Server.hpp"

// SILVER == retour de la fonction
// GREEN == tout ce qui est lancé par la classe Server
// RED == Tout ce qui est lancé par User
// BLUE == Tout ce qui est lancé par Channel
// VIOLET == Command

namespace ft
{
	class Command;
	class User;
	class Server;

	// void	print_command(Command * cmd);
	void	print_User(User * user);
	//void	print_server(Server * srv);
	// void	print_UserList(Users);
}

#endif


