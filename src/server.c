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

# include "cub3D.h"

int main(int argc, char *argv[])
{
	int					master_socket;
	int					new_socket;
	int					read_size;
	int					client_socket[MAX_CLIENT];
	int					i;
	int					j;
	int					opt;
	int					addrlen;
	char				client_message[2000];
	struct sockaddr_in	serv_addr;
	int					n_players;
	char				buffer[1025];
	time_t				ticks;
	fd_set				read_fds;
	t_vector2			players_pos[MAX_CLIENT];

	(void)argc;
	(void)argv;
	n_players = 0;
	printf("Cub3D server\n");
	i = -1;
	while (++i < MAX_CLIENT)
		client_socket[i] = 0;
	master_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (master_socket < 0)
	{
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}
	if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR,
		(char *)&opt, sizeof(opt)) < 0)
	{
		perror("Setsockopt failed");
		exit(EXIT_FAILURE);
	}	
	// ft_memset(&serv_addr, '0', sizeof(serv_addr));
	// ft_memset(sendBuff, '0', sizeof(sendBuff));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PORT);

	/* The call to the function "bind()" assigns the details specified
	 * in the structure 『serv_addr' to the socket created in the step above
	 */
	if (bind(master_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}	
	printf("Bind done\n");

	/* The call to the function "listen()" with second argument as 10 specifies
	 * maximum number of client connections that server will queue for this listening
	 * socket.
	 */
	if (listen(master_socket, MAX_CLIENT) < 0)
	{
		perror("Listen failed");
		exit(EXIT_FAILURE);
	}	
	printf("Listening on port %d\n", PORT);

	addrlen = sizeof(serv_addr);
	printf("Waiting for connections\n");
	int	max_sd;
	int	sd;
	int	activity;
	i = -1;
	while (++i < MAX_CLIENT)
		players_pos[i].x = -1.0;
	while(1)
	{
		usleep(1000);
		FD_ZERO(&read_fds);
		FD_SET(master_socket, &read_fds);
		max_sd = master_socket;
		i = -1;
		while (++i < MAX_CLIENT)
		{
			sd = client_socket[i];
			if (sd > 0)
				FD_SET(sd, &read_fds);
			if (sd > max_sd)
				max_sd = sd;
		}
		activity = select(max_sd + 1, &read_fds, NULL, NULL, NULL);
		if (activity < 0 && errno != EINTR)
		{
			perror("Select failed");
			exit(EXIT_FAILURE);
		}
		if (FD_ISSET(master_socket, &read_fds))
		{
			new_socket = accept(master_socket, (struct sockaddr*)&serv_addr, (socklen_t *)&addrlen);
			if (new_socket < 0)
			{
				perror("Accept failed");
				exit(EXIT_FAILURE);
			}
			printf("New connection fd%d , ip: %s\n",
				new_socket , inet_ntoa(serv_addr.sin_addr));
			if (send(new_socket, "Connected to Cub3D server!\n", 28, 0) != 28)
				perror("Send");
			n_players++;
			i = -1;
			while (++i < MAX_CLIENT)
			{
				if (client_socket[i] == 0)
				{
					client_socket[i] = new_socket;
					printf("Adding to list of socket as %d\n", i);
					if (send(new_socket, &i, sizeof(i), 0) != sizeof(i))
						perror("Send");
					break ;
				}
			}
		}
		int	id;
		id = -1;
		int	valread;
		while (++id < MAX_CLIENT)
        {
            sd = client_socket[id];
            if (FD_ISSET(sd, &read_fds))
            {
				ft_bzero(buffer, sizeof(buffer));
				valread = read(sd, buffer, 1024);
				write(sd, &n_players, sizeof(n_players));
                if (valread == 0)
                {
					players_pos[id].x = -1.0;
					n_players--;
                    getpeername(sd , (struct sockaddr*)&serv_addr,
						(socklen_t*)&addrlen);
                    printf("Host disconnected , id %d , fd %d\n",
                          id , sd);
                    close(sd);
                    client_socket[id] = 0;
                }
                else
                {
					// RESPONSE
                    buffer[valread] = '\0';
                    // send(sd , buffer , strlen(buffer) , 0 );
					ft_memcpy(&players_pos[id], buffer, sizeof(t_vector2));
					printf("Id:%d fd:%d	%.2f %.2f\n", id, sd, players_pos[sd].x, players_pos[sd].y);
					ft_bzero(buffer, sizeof(buffer));
					j = -1;
					while (++j < 10)
						ft_memcpy(buffer + j * (sizeof(t_vector2)), &players_pos[j], sizeof(t_vector2));
					j = -1;
					while (++j < 10)
						printf("Player: %d	%.2f %.2f\n", j,
							((t_vector2 *)(buffer + j * sizeof(t_vector2)))->x,
							((t_vector2 *)(buffer + j * sizeof(t_vector2)))->y);
					print_tab_pos(players_pos);
					write(sd, buffer, ft_strlen(buffer));
                }
            }
        }
	}
}
