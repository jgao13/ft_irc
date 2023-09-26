#include "../include/Network.hpp"

namespace ft
{

Network::Network(/* args */)
{
	std::cout << "Network created but it shouldn't have been\n";
}

Network::Network(long int port)
{
	init_server_socket(port);
}

Network::~Network()
{
	for (std::vector<int>::iterator it = _list_fd.begin(); it != _list_fd.end(); it++)
		close(*it);
}


int	Network::init_server_socket(long int port)
{
	const int opt = 1;
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		// _list_fd.push_back(server_fd);
		close(server_fd);
		throw std::runtime_error(std::string("socket failed: ") + strerror(errno));
	}
	std::cout << "Server fd == " << server_fd << std::endl;
	if (int ret = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0)
	{
		std::cout << "ret == " << ret << std::endl;
		throw std::runtime_error(std::string("setsockopt failed: ") + strerror(errno));
	}
	if (fcntl(server_fd, F_SETFL, opt | O_NONBLOCK) < 0)
		throw std::runtime_error(std::string("fcntl failed: ") + strerror(errno));
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	int ret = bind(server_fd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr));
	if (ret != 0)
		throw std::runtime_error(std::string("bind failed: ") + strerror(errno));
	const int backlog = 128;
	ret = listen(server_fd, backlog);
	if (ret != 0)
		throw std::runtime_error(std::string("listen failed: ") + strerror(errno));

	return (server_fd);
}

	int	Network::init_socket(unsigned int addrs)
	{
		int	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (socket_fd == -1)
		{
			for (int i = 0; i < 4; i++)
			{
				socket_fd = socket(AF_INET, SOCK_STREAM, 0);
				if (socket_fd != -1)
					break;
			}
			if (socket_fd == -1)
				throw std::runtime_error(std::string("socket failed"));
		}

		const int opt = 1;
		int ret = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
		if (ret < 0)
			throw std::runtime_error(std::string("setsockopt failed: ") + strerror(errno));
		ret = fcntl(socket_fd, F_SETFL, O_NONBLOCK);
		sockaddr_in my_addr;
		if (ret != 0)
			throw std::runtime_error(std::string("fcntl failed: ") + strerror(errno));
		my_addr.sin_family = AF_INET;
		my_addr.sin_port = htons(addrs);

		ret = bind(socket_fd, (struct sockaddr *) &my_addr, sizeof(sockaddr_in));
		if (ret != 0)
			throw std::runtime_error(std::string("bind failed: ") + strerror(errno));
		const int backlog = 128;
		ret = listen(socket_fd, backlog);
		if (ret != 0)
			throw std::runtime_error(std::string("listen failed: ") + strerror(errno));
		_list_fd.push_back(socket_fd);
		return (socket_fd);
	}

	int	Network::make_socket_non_blocking(int sfd)
	{
		int	flags, s;

		flags = fcntl(sfd, F_GETFL, 0);
		if (flags == -1)
			throw(std::runtime_error("fcntl a merdé\n"));

		s = fcntl (sfd, F_SETFL, flags);
		if (s == -1)
			throw(std::runtime_error("fcntl a merdé\n"));
		return (0);
	}

	int		Network::getServerFd() const
	{
		return (server_fd);
	}

}

