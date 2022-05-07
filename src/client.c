# include "../inc/cub3D.h"

void	print_tab_pos(t_vector2 tab[10])
{
	int	i;

	i = -1;
	while (++i < 10)
		printf("%d, %.2f %.2f\n", i, tab[i].x, tab[i].y);
}

int	serv_process(t_vars *vars)
{
	unsigned long	n;
	int				r;
	t_packet		buf;

	n = 0;
	r = 0;
	send(vars->mult_fd, &vars->player.pos, sizeof(t_vector2), 0);
	//printf("Sent |%.2f %.2f|\n", vars->player.pos.x, vars->player.pos.y);
	while (n < sizeof(t_packet))
	{
		r = read(vars->mult_fd, &(buf) + n, sizeof(t_packet));
		if (r < 0)
		{
			printf("Read failed\n");
			return (1);
		}
		if (r == 0)
		{
			printf("Server closed\n");
			return (1);
		}
		if (n == 0 && *(int *)(&buf) == -1)
		{
			printf("Size error\n");
			return (0);
		}
		n += r;
	}
	if (buf.n_players > vars->mult_n_players &&
		vars->mult_n_players > 0 && buf.n_players <= MAX_CLIENT)
		printf("A player joined the game!\n");
	vars->mult_n_players = buf.n_players;
	ft_memcpy(vars->mult_positions, buf.players_pos, sizeof(t_vector2) * MAX_CLIENT);
	// print_tab_pos(vars->mult_positions);
	// printf("Players: %d id %d\n", buf.n_players, vars->mult_id);


	// if (vars->mult_n_players == 0)
	// {
	// 	vars->mult_id = (*(int *)vars->buffer) - 1;
	// 	printf("Players: %d %d\n", *(int *)vars->buffer, vars->mult_id);
	// }
	// ft_memmove(vars->buffer, vars->buffer + sizeof(int), sizeof(vars->buffer));
	//print_tab_pos((t_vector2 *)vars->buffer);
	// ft_memcpy(vars->mult_positions,
	//  		vars->buffer, sizeof(vars->mult_positions));
	// n = -1;
	// while (++n < MAX_CLIENT)
	// {
	// 	// printf("Player: %d	%.2f %.2f\n", n,
	// 	// 	((t_vector2 *)(vars->buffer + n * sizeof(t_vector2)))->x,
	// 	// 	((t_vector2 *)(vars->buffer + n * sizeof(t_vector2)))->y);
	// 	ft_memcpy(&vars->mult_positions[n], vars->buffer + n * sizeof(t_vector2), sizeof(t_vector2));
	// }
	// ft_bzero(vars->buffer, sizeof(vars->buffer));
	// n = -1;
	// while (++n < MAX_CLIENT)
	// {
	// 	// if (vars->mult_positions[n].x > 0)
	// 	printf("Player: %d	%.2f %.2f\n", n, vars->mult_positions[n].x, vars->mult_positions[n].y);
	// }
	return (0);
}

int serv_connect(t_vars *vars)
{
	int	n;

	vars->keyboard[46] = 0;
	vars->mult_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(vars->mult_fd < 0)
	{
		perror("Could not create socket");
		return (1);
	}
	ft_bzero(&vars->serv_addr, sizeof(vars->serv_addr));
	ft_bzero(vars->buffer, 1025);
	vars->serv_addr.sin_family = AF_INET;
	vars->serv_addr.sin_port = htons(PORT);
	if(inet_pton(AF_INET, SERVER_IP, &vars->serv_addr.sin_addr) <= 0)
	{
		perror("inet_pton error\n");
		return (1);
	}
	if(connect(vars->mult_fd, (struct sockaddr *)&vars->serv_addr, sizeof(vars->serv_addr)) < 0)
	{
		vars->mult_fd = 0;
		printf("Connect Failed\n");
		return (0);
	}
	n = 0;
	printf("Connected\n");
	// while (n < 28 + sizeof(int))
	// {
	// 	n += read(vars->mult_fd, vars->buffer + n, sizeof(vars->buffer));
	// }
	n = read(vars->mult_fd, vars->buffer, sizeof(vars->buffer));
	vars->mult_id = *(int *)vars->buffer;
	printf("ID %d\n", vars->mult_id);
	ft_memmove(vars->buffer, vars->buffer + sizeof(int), sizeof(vars->buffer));
	printf("%s\n", vars->buffer);
	// ft_memmove(vars->buffer, ft_strchr(vars->buffer, '\0'), sizeof(vars->buffer));
	ft_bzero(vars->buffer, sizeof(vars->buffer));
	return 0;
}