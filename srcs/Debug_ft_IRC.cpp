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

	void	print_User(User * user)
	{
		std::cout << ORANGE << "\nprint_User called:-----------\n"
		<< "_userfd: " << RESET << user->getUserFd() << ORANGE
		<< "\n_username: " << RESET << user->getUsername() << ORANGE
		<< "\n_nickname: " << RESET << user->getNickname() << ORANGE
		<< "\n_firstname: " << RESET << user->getFirstName() << ORANGE
		<< "\n_lastname: " << RESET << user->getLastName() << ORANGE
		<< "\n_status: " << RESET << user->printStatus()
		<< "\n-------------------------------------------------\n";
	}

	/////////////////////ajout du print
//mes ajout --> pas encore tester
	// void	print_epoll_setup(Server * server)
	// {
	// 	std::cout << "\nepoll fd: " << server->_epoll_fd << std::endl;
	// 	std::cout << "epoll running " << server->_running << std::endl;
	// 	std::cout << "epoll_event: " << " pas fait" << std::endl;
	// 	std::cout << "epoll listen_list: ";
	// 	for (int i = 0; i < server->listen_list.size(); i++)
	// 	{
	// 		if (i !=  0)
	// 			std::cout << ", ";
	// 		std::cout << server->listen_list[i];
	// 	}
	// 	std::cout << std::endl;
	// }

	// void	print_server_part(Server * server)
	// {
	// 	std::map<int, User*>::iterator begin = server->_userList.begin();
	// 	std::map<int, User*>::iterator end = server->_userList.end();

	// 	std::cout << "\n _userlist: ";
	// 	while (begin != end)
	// 	{
	// 		std::cout << begin->first << " => " << begin->second << std::endl;
	// 		begin++;
	// 	}
	// 	std::cout << "end of _userlist\n";
	// 	std::cout << "_server_password: " << server->_server_password << std::endl;
	// 	std::cout << "_serverName: " << server->_serverName << std::endl;
	// 	std::cout << "Channel list et Command_list a faire\n";
	// 	std::cout << "_list_connected_users: ";
	// 	for (int i = 0; i < server->_list_connected_users.size(); i++)
	// 	{
	// 		if (i != 0)
	// 			std::cout << ", ";
	// 		std::cout << server->_list_connected_users[i];
	// 	}
	// 	std::cout << std::endl;
	// }
	// void	print_server(Server * server)
	// {
	// 	std::cout << PURPLE << "SERVER:\n----------\n";
	// 	print_epoll_setup(server);
	// 	print_server_part(server);
	// 	std::cout << "\n-----END OF SERVER CHECK-------\n";
	// }

}