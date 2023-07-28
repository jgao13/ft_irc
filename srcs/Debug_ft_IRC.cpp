#include "../include/Debug_ft_IRC.hpp"

namespace ft
{
	void	print_command(Command * cmd)
	{
		std::cout << PURPLE << "COMMAND:\n--------\n"
		<< "_command : " << SILVER << cmd->command() << PURPLE
		<< "\narguments : " << SILVER;
		for (int i = 0; i < cmd->arguments().size(); i++)
			{
				if (i != 0)
					std::cout << ", ";
				std:: cout << (cmd->arguments())[i];
			}
			std::cout << "\n";
		std::cout << PURPLE << "_message : " << SILVER << cmd->message();
	}
}