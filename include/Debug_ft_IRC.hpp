#ifndef DEBUG_FT_IRC
# define DEBUG_FT_IRC

# include <string>
# include "Colors.hpp"
# include "Command.hpp"

// SILVER == retour de la fonction
// GREEN == tout ce qui est lancé par la classe Server
// ORANGE == Tout ce qui est lancé par User
// BLUE == Tout ce qui est lancé par Channel
// VIOLET == Command Class et toutes les commandes

namespace ft
{
	class Command;
	class User;
	class Server;

	// void	print_command(Command * cmd);
	void	print_User(User * user);
	// void	print_UserList(Users);
}

#endif


