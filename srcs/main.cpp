#include "../include/Server.hpp"
#include "../include/Colors.hpp"
#include "../include/Utils.hpp"
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

bool g_stop = false;

void handler(int) { g_stop = true; }

// int	main()
int	main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "Usage == ./ft_irc_server <port> <password>\n";
		return -(1);
	}

	// (void)av;

	try 
	{
		ft::Server	server(av[1], av[2]);
		// ft::Server	server("8080", "pipicaca");
		std::cout << "SERVER UP\n";
		signal(SIGINT, handler);
		server.init_epoll();
		std::cout << "EPOLL UP\n"; 
		while (!g_stop)
			server.run_Server();
	}
	catch (std::exception & e) 
	{
		std::cout << e.what() << std::endl;
		std::cout << strerror(errno)<< std::endl;
		// Ya moyen que strerrorname_np soit pas autorisé, ca gave un peu
		// std::cout << "ERRNO == " << errno << ", LETTER CODE == " << strerrorname_np(errno) << std::endl;
		return (-1);
		// server.clearFd();
	}

	return(0);
}

		// 1. CREATE SOCKET AND BIND
		// 2. MAKE SOCKET NON BLOCKING
		// 3. PUT SOCKET ON LISTEN
		// 4. EPOLL CREATE1 (RETURN A FILE DESCRIPTOR TO THE EPOLL)
		// 5. EPOLL CONFIGURATION
		// 6. EPOLL CTL, ADD ENTRY OF EVENT FOR A DESIGNATED FILE DESC.
		// 7. TABLE OF EVENTS CREATION

		// ******************** LOOP ACTION BBY ************************
		// while(1)
		// 8. epoll_wait: Attend un certain temps et mets tous les events
		// dans le tableau d'events
		// 9. Check de probleme d'epoll pour chaque event
		// 10. Si un event concerne le fd du socket: 
			// 10-1: On l'accepte
			// 10-2: (optionnel) on peut imprimer les infos du socket entrant
			// 10-3: On passe le socket entrant en non-bloquant ()
			// 10-4: On reconfigure le event (histoire de pas avoir a new, mais 
			// ptetre quon aura besoin du event)
			// 10-5: on rajoute le event a la liste de epoll a monitorer
		// 11. Sinon: while(1)
			// 11-1: read(events[i].data.fd, buf; BUFF_SIZE);
			// 11-2: si errno == EAGAIN: all data has been read, mais nous
			// ya moyen quon s'en tape, par contre gestion de crlf pour notre pomme
			// 11-3 si count de read == 0, the remote has closed the connection
			// 11-4: La du coup on peut ecrire ce quon a recu
/*
		ORDRE:
	1.
*/