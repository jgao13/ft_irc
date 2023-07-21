/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthibaut <tthibaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:00:47 by tthibaut          #+#    #+#             */
/*   Updated: 2023/04/03 14:19:01 by tthibaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <sys/types.h>	//pour les types, optionnel sur les plateformes POSIX1
#include <sys/socket.h>		// socket et plein d'autres trucs
#include <sys/epoll.h>		//epoll stuff
#include <unistd.h>
#include <stdlib.h>			//exit function
#include <errno.h>			//perror
#include <stdio.h>			//perror
#include <string>
#include <iostream>
#include <limits.h>			//pour sizeof
#include <sys/types.h>		//pour getaddrinfo
#include <netdb.h>			// pour getaddrinfo
#include <sys/un.h>			// pour les sockaddr_un


struct Server
{
	int	socket_fd;
	int	epoll_fd;
	int	listen_sock;
	int	conn_sock;
	std::string	password;



};
/*To accept connections, the following steps are performed:

           1.  A socket is created with socket(2).

           2.  The socket is bound to a local address using bind(2), so that other sockets may be connect(2)ed to it.

           3.  A willingness to accept incoming connections and a queue limit for incoming connections are specified with listen().

           4.  Connections are accepted with accept(2).

*/


#define BUF_SIZE 500
int	main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;
    ssize_t nread;
    char buf[512];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    s = getaddrinfo(NULL, argv[1], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    /* getaddrinfo() returns a list of address structures.
       Try each address until we successfully bind(2).
       If socket() (or bind()) fails, we (close the socket
       and) try the next address. */

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */

        close(sfd);
    }

    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);           /* No longer needed */

    /* Read datagrams and echo them back to sender */

    for (;;) {
        peer_addr_len = sizeof(struct sockaddr_storage);
        nread = recvfrom(sfd, buf, BUF_SIZE, 0,
                (struct sockaddr *) &peer_addr, &peer_addr_len);
        if (nread == -1)
            continue;               /* Ignore failed request */

        char host[NI_MAXHOST], service[NI_MAXSERV];

        s = getnameinfo((struct sockaddr *) &peer_addr,
                        peer_addr_len, host, NI_MAXHOST,
                        service, NI_MAXSERV, NI_NUMERICSERV);
       if (s == 0)
            printf("Received %ld bytes from %s:%s\n",
                    (long) nread, host, service);
        else
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));

        if (sendto(sfd, buf, nread, 0,
                    (struct sockaddr *) &peer_addr,
                    peer_addr_len) != nread)
            fprintf(stderr, "Error sending response\n");
    }
}

int	init_serv(Server server)
{
	int	fd_serv;
	//1. Socket Creation
	server.socket_fd = socket(AF_INET6, SOCK_STREAM, 0);

	//2. Bind (a proteger)
	struct sockaddr_un my_addr;
	bind(server.socket_fd, (struct sockaddr *) &my_addr, sizeof(struct addrinfo));

	//3. epoll Creation
	server.epoll_fd = epoll_create(0);
	if (server.epoll_fd == -1)
	{
		perror("epoll_create1");
		exit(EXIT_FAILURE);
	}

	//4. listen mode, avec le nombre max de connections
	if (listen(server.socket_fd, 512) == -1)
		exit(EXIT_FAILURE);


}

// int	main(int ac, char **av)
// {
// 	if (ac != 3)
// 		return;
// 	Server	server;
// 	if (init_serv(server) == -1)
// 		exit(-1);
// 	while(1)
// 		accept4(server.socket_fd, SOCK_NONBLOCK)
// }
