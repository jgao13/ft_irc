#include "../include/Command.hpp"
// #include "../include/Color.hpp"

namespace	ft
{
	Command::Command(std::string message, Server * server, User * user) : _server(server), _user(user), _command(std::string())
	{
		size_t 		position;
		std::string	delimiter(":");

		if (message.empty())
			return;

		// Isole la command, IE tout ce qu'il y a avant le ':',
		// IE avant délimiteur == Command + argument
		// apres délimiteur == message.
		if ((position = message.find(delimiter)) != std::string::npos)
		{
			std::string tmp = message.substr(0, position);
			message.erase(0, position + delimiter.length());
			_message = message;
			message = tmp;
		}

		_arguments = ft::split(message, " ");
		_command = *(_arguments.begin());
		_arguments.erase(_arguments.begin());
		_command = strToUpper(_command);
		for (int i = 0; i < _arguments.size(); ++i)
			_argument += _arguments[i];
		if (DEBUG)
			print_command();
	}

	//	GETTERS
	std::vector<std::string>	Command::arguments() const {return (_arguments);}
	std::string					Command::message() const {return (_message);}
	std::string					Command::command() const {return (_command);}
	std::string					Command::argument() const {return (_argument);}		

	//	CONSTRUCTOR AND DESTRUCTOR
	Command::Command(){/*This shouldn't be used*/}
	Command::~Command() {}

	int Command::print_command() 
	{
		std::cout << PURPLE;
		std::cout << "Command Information:" << std::endl;
		std::cout << "  Command: " << _command << std::endl;

		std::cout << "  Arguments: ";
		for (size_t i = 0; i < _arguments.size(); ++i) {
			std::cout << _arguments[i];
			if (i < _arguments.size() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << std::endl;

		std::cout << "  Message: " << _message << std::endl;
		std::cout << "  Prefix: " << _prefix << std::endl;

		// If you want to print information about the associated user or server, you can do so here
		// For example:
		// if (_user) {
		//     std::cout << "  User: " << _user->nickname() << std::endl;
		// }
		// if (_server) {
		//     std::cout << "  Server: " << _server->name() << std::endl;
		// }

		std::cout << RESET; // Reset text color to default
		return 0;
	}
}
