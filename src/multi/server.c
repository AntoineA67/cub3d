/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:13:07 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/31 13:51:22 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

int main(int argc, char *argv[])
NOPROF
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
	char				buffer[1025];
	t_vector2			read_buf;
	time_t				ticks;
	fd_set				read_fds;
	t_packet			packet;
	int	id;
	int	valread;

	(void)argc;
	(void)argv;
	packet.n_players = 0;
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
		packet.players_pos[i].x = -1.0;
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
			if (send(new_socket, &packet.n_players, sizeof(int), 0) != sizeof(int))
				perror("Send");
			if (send(new_socket, "Connected to Cub3D server!\n", 28, 0) != 28)
				perror("Send");
			packet.n_players++;
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
		id = -1;
		while (++id < packet.n_players)
        {
			usleep(1000);
            sd = client_socket[id];
            if (FD_ISSET(sd, &read_fds))
            {
				// ft_bzero(buffer, sizeof(buffer));
				// valread = read(sd, buffer, 1024);
				ft_bzero(&read_buf, sizeof(t_vector2));
				valread = read(sd, &read_buf, sizeof(t_vector2));
                if (valread == 0)
                {
					packet.players_pos[id].x = -1.0;
					packet.n_players--;
                    getpeername(sd , (struct sockaddr*)&serv_addr,
						(socklen_t*)&addrlen);
                    printf("Player with id %d disconnected\n", id);
                    close(sd);
                    client_socket[id] = 0;
                }
				else if (valread != sizeof(t_vector2))
				{
					printf("Size error\n");
					*(int *)buffer = -1;
					send(sd, buffer, sizeof(int), 0);
				}
                else
                {
					// RESPONSE
                    buffer[valread] = '\0';
                    // send(sd , buffer , strlen(buffer) , 0 );
					if (packet.players_pos[id].x < 0
						|| (fabs(packet.players_pos[id].x - read_buf.x) < 1
						&& fabs(packet.players_pos[id].y - read_buf.y) < 1))
					{
						packet.players_pos[id].x = read_buf.x;
						packet.players_pos[id].y = read_buf.y;
					}
					// ft_memcpy(&packet.players_pos[id], &read_buf, sizeof(t_vector2));
					printf("Id:%d fd:%d	%.2f %.2f\n", id, sd, packet.players_pos[id].x, packet.players_pos[id].y);
					ft_bzero(buffer, sizeof(buffer));
					j = -1;
					while (++j < MAX_CLIENT)
						ft_memcpy(buffer + j * (sizeof(t_vector2)), &packet.players_pos[j], sizeof(t_vector2));
					j = -1;
					while (++j < packet.n_players)
						printf("Player: %d	%.2f %.2f\n", j,
							((t_vector2 *)(buffer + j * sizeof(t_vector2)))->x,
							((t_vector2 *)(buffer + j * sizeof(t_vector2)))->y);
					if (send(sd, &packet, sizeof(t_packet), 0) != sizeof(packet))
						printf("Error while sending\n");
					// write(sd, &packet.n_players, sizeof(packet.n_players));
					// print_tab_pos(packet.players_pos);
					// write(sd, buffer, ft_strlen(buffer));
                }
            }
        }
	}
}
