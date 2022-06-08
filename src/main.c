/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:42:07 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/08 13:18:17 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

long	gettime(long initime)
NOPROF
{
	long			res;
	struct timeval	time;

	gettimeofday(&time, NULL);
	res = time.tv_usec / 1000;
	res += time.tv_sec * 1000;
	res -= initime;
	return (res);
}

void	init_imgs(t_vars *vars)
{
	vars->img = ft_calloc(1, sizeof(t_data));
	vars->img2 = ft_calloc(1, sizeof(t_data));
	vars->settings.bttext = ft_calloc(10, sizeof(t_data));
	load_texture(vars, "start", 0, "./textures/pack_blue_pink/start.xpm");
	load_texture(vars, "settings", 0, "./textures/pack_blue_pink/settings.xpm");
	load_texture(vars, "maps", 0, "./textures/pack_blue_pink/maps.xpm");
	load_texture(vars, "textures", 0, "./textures/pack_blue_pink/textures.xpm");
	load_texture(vars, "no", 0, vars->no);
	load_texture(vars, "aaa", 0, "./textures/nice/aaa.xpm");
	load_texture(vars, "hp", 0, "./textures/hp.xpm");
	load_texture(vars, "end", 0, "./textures/xpm/dirt.xpm");
	load_texture(vars, "hud", 0, "./textures/hud.xpm");
	load_texture(vars, "bullet", 0, "./textures/bullets/bullet.xpm");
	load_texture(vars, "so", 0, vars->so);
	load_texture(vars, "maps", 0, "./textures/pack_blue_pink/maps.xpm");
	load_texture(vars, "ea", 0, "./textures/xpm/banane.xpm");
	load_texture(vars, "we", 0, vars->we);
}

void	init_bullets(t_vars *vars)
{
	int	i;

	vars->bullet_cooldown = -1;
	i = -1;
	while (++i < MAX_BULLETS)
	{
		vars->bullets[i].pos.x = -1;
	}
}

void	init_enemies(t_vars *vars)
{
	int				i;
	int				n;
	double			prob;
	struct timeval	time;

	i = 0;
	//(int)(gettime(vars->n1) % 100)
	// i = -1;
	n = -1;
	prob = .0001;
	while (vars->max_n_enemies < vars->usable_cells / 20 + 1)
	{
		gettimeofday(&time, NULL);
		//printf("GEN ENEMY: %d %.2f %d %.2f\n", vars->max_n_enemies, prob, (int)(time.tv_usec) % 100, prob * 100);
		if (vars->parse_seen[i] == 1
			&& abs((int)vars->player.pos.x - i % vars->size.x) > 2 && abs((int)vars->player.pos.y - i % vars->size.y) > 2
			&& (int)(time.tv_usec) % 100 < (int)(prob * 100))
		{
			vars->enemies[++vars->max_n_enemies - 1].lives = 3;
			vars->enemies[vars->max_n_enemies - 1].last_attack = -1000;
			vars->enemies[vars->max_n_enemies - 1].pos.x = i % vars->size.x + .5;
			vars->enemies[vars->max_n_enemies - 1].pos.y = i / vars->size.x + .5;
			ft_memcpy(&vars->enemies[vars->max_n_enemies - 1].last_player_pos,
				&vars->enemies[vars->max_n_enemies - 1].pos, sizeof(t_vector2));
			printf("Enemy: %.2f %.2f\n", vars->enemies[vars->max_n_enemies - 1].pos.x,
				vars->enemies[vars->max_n_enemies - 1].pos.y);
			prob = 0.0;
		}
		if (vars->parse_seen[i] == 1)
			prob += 1.0 / vars->usable_cells;
		i = (i + 1) % vars->size.z;
	}

	// while (++i < vars->size.z && vars->max_n_enemies < vars->usable_cells / 20 + 1)
	// {
	// 	if (vars->parse_seen[i] == 1 && ++n % (int)(vars->usable_cells / 10) == 0)
	// 	{
	// 		vars->enemies[++vars->max_n_enemies - 1].lives = 3;
	// 		vars->enemies[vars->max_n_enemies - 1].last_attack = -1000;
	// 		vars->enemies[vars->max_n_enemies - 1].pos.x = i % vars->size.x + .5;
	// 		vars->enemies[vars->max_n_enemies - 1].pos.y = i / vars->size.x + .5;
	// 		ft_memcpy(&vars->enemies[vars->max_n_enemies - 1].last_player_pos,
	// 			&vars->enemies[vars->max_n_enemies - 1].pos, sizeof(t_vector2));
	// 		printf("Enemy: %.2f %.2f\n", vars->enemies[vars->max_n_enemies - 1].pos.x,
	// 			vars->enemies[vars->max_n_enemies - 1].pos.y);
	// 	} 
	// }
	vars->n_enemies = vars->max_n_enemies;
}

static void	fill_vars(t_vars *vars, int fd)
{
	vars->max_n_enemies = 0;
	vars->mult_n_players = 0;
	vars->usable_cells = 0;
	vars->player.run = 0;
	vars->jump_height = 0.0;
	vars->jump = -2000;
	vars->ao = 1.0;
	vars->ao_scale = .22;
	vars->settings.y_ratio_mouse_speed = 1.2;
	vars->settings.x_ratio_mouse_speed = 1.2;
	vars->mult_fd = 0;
	vars->scroll = 0;
	affect_ascii(vars);
	ft_bzero(vars->keyboard, sizeof(vars->keyboard));
	vars->mlx = mlx_init();
	vars->win_size.x = 1920;// * 0.75;
	vars->win_size.y = 1080;// * 0.75;
	vars->rays = ft_calloc(vars->win_size.x + 1, sizeof(t_ray));
	vars->map = parse(fd, vars);
	vars->tx = (2.0 / vars->win_size.x);
	vars->size.z = vars->size.x * vars->size.y;
	vars->max_size = ft_max(vars->size.x, vars->size.y);
	if (init_player(vars))
		return ; //NO PLAYER IN MAP
	vars->parse_seen = ft_calloc(vars->size.z + 1, 1);
	if (!vars->parse_seen)
		return ;
	if (check_map(vars, (int)vars->player.pos.x, (int)vars->player.pos.y))
	{
		write(2, "Error while parsing map\n", 25);
		exit(EXIT_FAILURE);
	}
	vars->enemies = ft_calloc(vars->usable_cells / 20 + 2, sizeof(t_enemy));
	printf("USABLE CELLS %d ENEMIES %d\n", vars->usable_cells, vars->usable_cells / 20 + 2);
	init_enemies(vars);
	free(vars->parse_seen);
	init_bullets(vars);
	init_imgs(vars);
	vars->img->img = mlx_new_image(vars->mlx, vars->win_size.x, vars->win_size.y);
	vars->img->addr = mlx_get_data_addr(vars->img->img, &vars->img->bits_per_pixel,
	 		&vars->img->line_length, &vars->img->endian);
	if (!vars->img->addr)
		return ;
	vars->img->bits_per_pixel /= 8;
	vars->img2->img = mlx_new_image(vars->mlx, vars->win_size.x, vars->win_size.y);
	vars->img2->addr = mlx_get_data_addr(vars->img2->img, &vars->img2->bits_per_pixel,
	 		&vars->img2->line_length, &vars->img2->endian);
	if (!vars->img2->addr)
		return ;
	vars->img2->bits_per_pixel /= 8;
	close(fd);
}

static char	*extract_name(char *str)
{
	if (ft_strrchr(str, '/'))
		return ((char *)(ft_strrchr(str, '/') + 1));
	return (str);
}

static int	test_hook(t_vars *vars)
{
	(void)vars;
	exit(EXIT_SUCCESS);
	// esc(vars, 0);
	return (0);
}

int	frame(void *data)
{
	t_vars	*vars;
	long	temp;
	char	*fps;
	char	*itoa;

	vars = (t_vars *)data;
	if (vars->mult_fd)
		serv_process(vars);
	if (!vars->ui)
	{
		temp = gettime(vars->n1);
		vars->delta_time = (temp + .0 - (vars->n3 + .0)) / 1000.0;
		check_inputs(vars);
		vars->n3 = temp;
		if (!vars->settings.fps_cap || !fmod(gettime(vars->n1), (1000 / (int)vars->settings.fps_cap)))
		{
			vars->delta_time_render = (temp + .0 - (vars->n2 + .0)) / 1000.0;
			itoa = ft_itoa(1000 / (temp - vars->n2));
			fps = ft_strjoin("FPS: ", itoa);
			// printf("%.10f|%s\n", vars->delta_time, itoa);
			render(vars);
			mlx_string_put(vars->mlx, vars->win, 100, 100, 0xff00ff, fps);
			free(itoa);
			free(fps);
			vars->n2 = temp;
		}
	}
	else
	{
		ft_int_memset(vars->img->addr, 0x000000,
		vars->img->line_length * vars->win_size.y / 4);
	if (vars->ui == 1)
	{
		ui_frame1(vars);
		vars->clicked = 0;
	}
	else if (vars->ui == 2)
	{
		ui_frame2(vars);
		vars->clicked = 0;
	}
	else if (vars->ui == 3)
	{
		ui_frame3(vars);
		vars->clicked = 0;
	}
	else if (vars->ui == 4)
	{
		ui_setting(vars);
		vars->clicked = 0;
	}
	else if (vars->ui == 5)
	{
		ui_texture(vars);
		vars->clicked = 0;
	}
	else if (vars->ui == 11)
	{
		if (gettime(vars->n1) - vars->n2 > 10000)
		{
			free_textures(vars);
			exit(0);
		}
	}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		fd;

	if (argc != 2)
	{
		perror("Argument error");
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("File error");
		exit(EXIT_FAILURE);
	}
	vars.min_map_mult = 16.0;
	vars.ui = 1;
	vars.n1 = gettime(0);
	fill_vars(&vars, fd);
	(void)extract_name;
	vars.rays_number = 0;
	vars.settings.fps_cap = 0;
	vars.settings.map_type = 1;
	vars.win = mlx_new_window(vars.mlx, vars.win_size.x,
			vars.win_size.y, extract_name(argv[1]));
	printf("EA: %s\nNO: %s\nSO: %s\nWE: %s\nF: %#x\nC: %#x\n",
		vars.ea, vars.no, vars.so, vars.we, to_rgb(vars.f, 0), to_rgb(vars.c, 0));
	mlx_do_key_autorepeatoff(vars.mlx);
	mlx_hook(vars.win, ON_KEYDOWN, 0, key_hook_down, &vars);
	mlx_hook(vars.win, ON_KEYUP, 0, key_hook_up, &vars);
	mlx_hook(vars.win, ON_MOUSEUP, 0, mouse_hook_up, &vars);
	mlx_hook(vars.win, ON_DESTROY, 0, test_hook, &vars);
	mlx_loop_hook(vars.mlx, frame, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	// mlx_loop_hook(vars.mlx, raycasting, &vars);
	mlx_loop(vars.mlx);
	free_textures(&vars);
}
