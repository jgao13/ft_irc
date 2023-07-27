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
//mes ajout --> pas encore tester
	void	print_epoll_setup(Server *srv)
	{
		std::cout << "\nepoll fd: " << srv._epoll_fd << std::endl;
		std::cout << "epoll running " << srv._running << std::endl;
		std::cout << "epoll_event: " << " pas fait" << std::endl;
		std::cout << "epoll listen_list: ";
		for (int i = 0; i < srv->listen_list().size(); i++)
		{
			if (i !=  0)
				std::cout << ", ";
			std::cout << (srv->listen_list())[i];
		}
		std::cout << std::endl;
	}

	void	print_part4(Server *srv)
	{
		std::map<int, User*>::iterator begin = srv->_userlist.begin();
		std::map<int, User*>::iterator end = srv->_userlist.end();

		std::cout << "\n _userlist: "
		while (begin != end)
		{
			std::cout << begin->first << " => " << begin->second << std::endl;
			begin++;
		}
		std::cout << "end of _userlist\n";
		std::cout << "_server_password: " << srv->_server_password << std::endl;
		std::cout << "_serverName: " << srv->_serverName << std::endl;
		std::cout << "Channel list et Command_list a faire\n";
		std::cout << "_list_connected_users: "
		for (int i = 0; i < srv->_list_connected_users().size(); i++)
		{
			if (i != 0)
				std::cout << ", ";
			std::cout << (srv->_list_connected_users())[i];
		}
		std::endl;
	}
	void	print_server(Server * srv)
	{
		std::cout << PURPLE << "SERVER:\n----------\n";
		print_epoll_setup(srv);
		print_part4(srv);
		<< "\n-----END OF SERVER CHECK-------\n";
	}
}