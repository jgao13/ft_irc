#include "../include/Command.hpp"

namespace	ft
{
	Command::Command(std::string message, Server * server, User * user) : _server(server), _user(user), _command(std::string())
	{
		size_t 		position;
		std::string	delimiter(":");

		if (message.empty())
			return;

		if ((position = message.find(delimiter)) != std::string::npos)
		{
			// Isole la command, IE tout ce qu'il y a avant le ':',
			// IE avant délimiteur == Command + argument
			// apres délimiteur == message.
			std::string tmp = message.substr(0, position);
			message.erase(0, position + delimiter.length());
			_message = message;
			message = tmp;
		}

		_arguments = ft::split(message, " ");
		_command = *(_arguments.begin());
		_arguments.erase(_arguments.begin());
		// We need the prefix in uppercase for reasons
		_command = strToUpper(_command);
	// for (size_t index = 0; index < prefix.length(); ++index)
	// 	prefix[index] = std::toupper(prefix[index]);
		if (DEBUG)
		{
			// std::cout << "\t*** MESSAGE AFTER PARSER ***\n" 
			// << "PREFIX == "<< this->_prefix
			// << "\nCOMMAND == " << this->_command
			// << "\nARGS == ";
			// // for (std::vector<std::string>::iterator it = _arguments.begin(); it != _arguments.end(); it++)
			// // {
			// // 	std::cout << *it;
			// // 	if (it != _arguments.end() - 1)
			// // 		std::cout << ", ";
			// // 	else
			// // 		std::cout << "\n\n";
			// // }
			// // other method
			// for (int i = 0; i < _arguments.size(); i++)
			// {
			// 	if (i != 0)
			// 		std::cout << ", ";
			// 	std:: cout << _arguments[i];
			// }
			std::cout << PURPLE << "_______________\nNEW COMMAND CREATED:\n" << RESET;
			
			print_command();
			std::cout << "\n\n";
		}
	}

	// std::string	Command::command() const 
	// {
	// 	if (_message.empty() || _command.empty())
	// 		return (std::string (""));
	// 	return _command;
	// }

	// int		Command::parse_message(std::string message)
	// {
	// 	std::string delimiter(":");
	// 	size_t position;
	// 	if ((position = message.find(delimiter)) != std::string::npos)
	// 	{
	// 		std::string tmp = message.substr(0, position);
	// 		message.erase(0, position + delimiter.length());
	// 		_message = message;
	// 		message = tmp;
	// 	}

	// 	_arguments = split(message, " ");
	// 	_prefix = *(parameters.begin());
	// 	_arguments.erase(parameters.begin());

	// for (size_t index = 0; index < prefix.length(); ++index)
	// 	prefix[index] = std::toupper(prefix[index]);
	// }
	std::vector<std::string>	Command::arguments() const {return (_arguments);}
	std::string					Command::message() const {return (_message);}
	std::string					Command::command() const {return (_command);}


	Command::Command(){/*This shouldn't be used*/}

	Command::~Command() {}

	void	Command::print_command(void)
	{
		std::cout << PURPLE << "COMMAND:\n--------\n"
		<< "_command : " << SILVER << this->command() << PURPLE
		<< "\narguments : " << SILVER;
		for (int i = 0; i < arguments().size(); i++)
			{
				if (i != 0)
					std::cout << ", ";
				std:: cout << (arguments())[i];
			}
			std::cout << "\n";
		std::cout << PURPLE << "_message : " << SILVER << message() << RESET << "\n";
	}
}