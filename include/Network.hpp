#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <cerrno>


namespace ft {

/*
						********** NETWORK *************
	This class creates, configures and manages all the stuff related to sockets and
	file descriptors.
	Not much else to say, all methods should take and return int for clarity 
	(IE no classes like Users or Channel).
	Error handling is yet to be determined, but this class must close all fds at
	the end.
	epoll handling will be dealt outside I guess.
*/
class Network
{
	private:

	public:
		int	init_server_socket(long int addrs);
		// Init, configure and 
		int		init_socket(unsigned int addrs);
		unsigned long	port;		// port for network magic
		int	make_socket_non_blocking(int sfd); // probablement a virer

	private:
		std::vector<int>	_list_fd;
		int				server_fd;	// no comment
	private:
		/* data */
	public:
		
	Network(/* args */);
	Network(long port);
	int		getServerFd() const;

	~Network();
};

// Network::Network(/* args */)
// {
// 	std::cout << "Network created\n";
// }

// Network::~Network()
// {
// 	for (std::vector<int>::iterator it = _list_fd.begin(); it != _list_fd.end(); it++)
// 		close(*it);
// }


// int	Network::init_server_socket(unsigned int port)
// {
// 	try 
// 	{
// 		server_fd = socket(AF_INET, SOCK_STREAM, 0);
// 		const int opt = 1;
// 		_list_fd.push_back(server_fd);
// 		int ret = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
// 		if (ret < 0)
// 			throw std::runtime_error(std::string("setsockopt failed: ") + strerror(errno));
// 		ret = fcntl(server_fd, F_SETFL, opt | O_NONBLOCK);
// 		if (ret != 0)
// 			throw std::runtime_error(std::string("fcntl failed: ") + strerror(errno));
// 		struct sockaddr_in addr = {};
// 		addr.sin_family = AF_INET;
// 		addr.sin_port = htons(port);
// 		ret = bind(server_fd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr));
// 		if (ret != 0)
// 			throw std::runtime_error(std::string("bind failed: ") + strerror(errno));
// 	}
// 	catch (const std::exception &e) {
// 		close(server_fd);
// 		throw e;
// 	}
// 	return (server_fd);
// }

// 	int	Network::init_socket(unsigned int addrs)
// 	{
// 		int	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
// 		if (socket_fd == -1)
// 		{
// 			for (int i = 0; i < 4; i++)
// 			{
// 				socket_fd = socket(AF_INET, SOCK_STREAM, 0);
// 				if (socket_fd != -1)
// 					break;
// 			}
// 			if (socket_fd == -1)
// 				throw std::runtime_error(std::string("socket failed"));
// 		}	

// 		const int opt = 1;
// 		int ret = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
// 		if (ret < 0)
// 			throw std::runtime_error(std::string("setsockopt failed: ") + strerror(errno));
// 		ret = fcntl(socket_fd, F_SETFL, O_NONBLOCK);
// 		sockaddr_in my_addr;
// 		if (ret != 0)
// 			throw std::runtime_error(std::string("fcntl failed: ") + strerror(errno));
// 		my_addr.sin_family = AF_INET;
// 		my_addr.sin_port = htons(addrs);
// 		//2. Bind (a proteger)
// 		ret = bind(socket_fd, (struct sockaddr *) &my_addr, sizeof(sockaddr_in));
// 		if (ret != 0)
// 			throw std::runtime_error(std::string("bind failed: ") + strerror(errno));
// 		const int backlog = 128;
// 		ret = listen(socket_fd, backlog);
// 		if (ret != 0)
// 			throw std::runtime_error(std::string("listen failed: ") + strerror(errno));
// 		_list_fd.push_back(socket_fd);
// 		return (socket_fd);
// 	}

// 	int	Network::make_socket_non_blocking(int sfd)
// 	{
// 		int	flags, s;

// 		flags = fcntl(sfd, F_GETFL, 0);
// 		if (flags == -1)
// 			throw(std::runtime_error("fcntl a merdé\n"));
		
// 		s = fcntl (sfd, F_SETFL, flags);
// 		if (s == -1)
// 			throw(std::runtime_error("fcntl a merdé\n"));
// 		return (0);
// 	}

}

