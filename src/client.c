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
	int	n;

	send(vars->mult_fd, &vars->player.pos, sizeof(t_vector2), 0);
	// printf("Sent |%.2f %.2f|\n", vars->player.pos.x, vars->player.pos.y);
	n = read(vars->mult_fd, vars->buffer, 1024);
	if (n < 0)
	{
		printf("Read failed\n");
		return (1);
	}
	if (n == 0)
	{
		printf("Server closed\n");
		return (1);
	}
	vars->buffer[n] = 0;
	vars->mult_n_players = *(int *)vars->buffer;
	vars->mult_id = vars->mult_n_players - 1;
	printf("Players: %d, id: %d\n", vars->mult_n_players, vars->mult_id);
	ft_memmove(vars->buffer, vars->buffer + sizeof(int), sizeof(vars->buffer));
	// print_tab_pos((t_vector2 *)vars->buffer);
	// ft_memcpy(vars->mult_positions,
	//  		vars->buffer, sizeof(vars->mult_positions));
	n = -1;
	while (++n < MAX_CLIENT)
	{
		// printf("Player: %d	%.2f %.2f\n", n,
		// 	((t_vector2 *)(vars->buffer + n * sizeof(t_vector2)))->x,
		// 	((t_vector2 *)(vars->buffer + n * sizeof(t_vector2)))->y);
		ft_memcpy(&vars->mult_positions[n], vars->buffer + n * sizeof(t_vector2), sizeof(t_vector2));
	}
	ft_bzero(vars->buffer, sizeof(vars->buffer));
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

	ft_bzero(vars->buffer, 1025);
	vars->mult_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(vars->mult_fd < 0)
	{
		perror("Could not create socket");
		return (1);
	}
	ft_bzero(&vars->serv_addr, sizeof(vars->serv_addr));
	vars->serv_addr.sin_family = AF_INET;
	vars->serv_addr.sin_port = htons(PORT);
	if(inet_pton(AF_INET, "127.0.0.1", &vars->serv_addr.sin_addr) <= 0)
	{
		perror("inet_pton error\n");
		return (1);
	}
	if(connect(vars->mult_fd, (struct sockaddr *)&vars->serv_addr, sizeof(vars->serv_addr)) < 0)
	{
		printf("Connect Failed\n");
		return (1);
	}
	n = read(vars->mult_fd, vars->buffer, 1024);
	vars->buffer[n] = 0;
	printf("%s\n", vars->buffer);
	ft_bzero(vars->buffer, sizeof(vars->buffer));
	return 0;
}