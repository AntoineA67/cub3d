/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:13:07 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/30 19:47:58 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../inc/cub3D.h"

/* --- server.c --- */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[])
{
	printf("Cub3D server\n");
	(void)argc;
	(void)argv;
	int listenfd = 0, connfd = 0, read_size;
	char client_message[2000];
	struct sockaddr_in serv_addr;

	char sendBuff[1025];
	time_t ticks;

	/* creates an UN-named socket inside the kernel and returns
	 * an integer known as socket descriptor
	 * This function takes domain/family as its first argument.
	 * For Internet family of IPv4 addresses we use AF_INET
	 */
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(sendBuff, '0', sizeof(sendBuff));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(5000);

	/* The call to the function "bind()" assigns the details specified
	 * in the structure 『serv_addr' to the socket created in the step above
	 */
	bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	dprintf(1, "Bind done\n");

	/* The call to the function "listen()" with second argument as 10 specifies
	 * maximum number of client connections that server will queue for this listening
	 * socket.
	 */
	listen(listenfd, 10);
	dprintf(1, "Listening\n");

	while(1)
	{
		/* In the call to accept(), the server is put to sleep and when for an incoming
		 * client request, the three way TCP handshake* is complete, the function accept()
		 * wakes up and returns the socket descriptor representing the client socket.
		 */
		connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
		if (connfd < 0)
		{
			dprintf(2, "Error while accepting connection\n");
			return (1);
		}
		dprintf(1, "Connection accepted\n");
		/* As soon as server gets a request from client, it prepares the date and time and
		 * writes on the client socket through the descriptor returned by accept()
		 */
		ticks = time(NULL);
		// while( (read_size = recv(connfd , client_message , 2000 , 0)) > 0 )
		// {
		// 	//Send the message back to client
		// 	dprintf(1, "MSG: %s\n", client_message);
		// 	write(connfd , client_message , strlen(client_message));
		// }
	
		snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
		// while (1)
		// 	write(connfd, "Ui", 2);
		write(connfd, sendBuff, strlen(sendBuff));
		close(connfd);
		sleep(1);
	}
}
