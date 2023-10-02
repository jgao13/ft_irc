#include "../include/Command.hpp"

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
		if (DEBUG)
		{
			// print_command(&this);
		}
	}

	//	GETTERS
	std::vector<std::string>	Command::arguments() const {return (_arguments);}
	std::string					Command::message() const {return (_message);}
	std::string					Command::command() const {return (_command);}

	//	CONSTRUCTOR AND DESTRUCTOR
	Command::Command(){/*This shouldn't be used*/}
	Command::~Command() {}

	int Command::print_command(){
    std::cout << "Command: " << _command << std::endl;
    std::cout << "Arguments: ";
    for (std::vector<std::string>::const_iterator it = _arguments.begin(); it!= _arguments.end(); ++it)
    {
        std::cout << "|" << *it << "| ";
    }
    std::cout << std::endl;
    std::cout << "Message: " << _message << std::endl;
    return (0);
    }
}
