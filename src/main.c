/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:42:07 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/11 11:50:04 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	init_player(t_vars *vars)
{
	char	*player_in_map;

	vars->player.rot.x = vars->start_rot;
	vars->player.rot.y = 0;
	vars->player.delta.x = 0;
	vars->player.delta.y = 0;
	player_in_map = ft_strchr(vars->map, 'P');
	vars->map[player_in_map - vars->map] = '0';
	vars->player.pos.x = (player_in_map - vars->map) % vars->size.x + .5;
	vars->player.pos.y = (player_in_map - vars->map) / vars->size.x + .5;
	return (0);
}

long	gettime(long initime)
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
	// t_textures	*imgs;

	vars->img = ft_calloc(1, sizeof(t_data));
	vars->img2 = ft_calloc(1, sizeof(t_data));
	vars->settings.bttext = ft_calloc(10, sizeof(t_data));
	load_texture(vars, "start", 0, "./textures/pack_blue_pink/start.xpm");
	load_texture(vars, "settings", 0, "./textures/pack_blue_pink/settings.xpm");
	load_texture(vars, "maps", 0, "./textures/pack_blue_pink/maps.xpm");
	load_texture(vars, "textures", 0, "./textures/pack_blue_pink/textures.xpm");
	load_animtexture(vars, "player", 4, "./textures/nice/photo.xpm");
	load_texture(vars, "no", 0, vars->no);
	//load_texture(vars, "oui", 0, "./textures/nice/non.xpm");
	load_texture(vars, "so", 0, vars->so);
	load_texture(vars, "maps", 0, "./textures/pack_blue_pink/maps.xpm");
	load_texture(vars, "ea", 0, "./textures/xpm/photo.xpm");
	load_texture(vars, "we", 0, vars->we);
}

static void	fill_vars(t_vars *vars, int fd)
{
	vars->player.run = 0;
	vars->jump_height = 0.0;
	vars->jump = -2000;
	vars->ao = 1.0;
	vars->ao_scale = .22;
	vars->settings.y_ratio_mouse_speed = 1.2;
	vars->settings.x_ratio_mouse_speed = 1.2;
	vars->mult_fd = 0;
	affect_ascii(vars);
	ft_bzero(vars->keyboard, sizeof(vars->keyboard));
	vars->mult_n_players = 0;
	vars->mlx = mlx_init();
	vars->win_size.x = 1920;// * 0.75;
	vars->win_size.y = 1080;// * 0.75;
	vars->map = parse(fd, vars);
	if (init_player(vars))
		return ; //NO PLAYER IN MAP
	vars->parse_seen = ft_calloc(vars->size.x * vars->size.y, 1);
	if (!vars->parse_seen)
		return ;
	if (check_map(vars, (int)vars->player.pos.x, (int)vars->player.pos.y))
	{
		write(2, "Error while parsing map\n", 25);
		exit(EXIT_FAILURE);
	}
	free(vars->parse_seen);
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
	// mlx_mouse_hide();
	// mlx_mouse_move(vars->win, 0, 0);
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

int	ui_frame1(t_vars	*vars)
{ 
	button(vars, screen_pc(25.15,50.05, gen_color(255,0,100, 100), vars), "0start", &change_ui);
	button(vars, screen_pc(25.30,25.025, gen_color(255,255,100, 0), vars), "2maps", &change_ui);
	button(vars, screen_pc(25.40,25.025, gen_color(25,60,100, 0), vars), "3textures", &change_ui);
	button(vars, screen_pc(25.50,25.025, gen_color(56,69,10, 0), vars), "4settings", &change_ui);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

int	ui_frame2(t_vars	*vars)
{ 
	button(vars, screen_pc(80.80,05.05, gen_color(255,0,100, 0), vars), "1start", &change_ui);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}
int	ui_frame3(t_vars	*vars)
{ 
	button(vars, screen_pc(80.80,05.05, gen_color(255,0,100, 0), vars), "1start", &change_ui);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

int	ui_setting(t_vars	*vars)
{
	button(vars, screen_pc(80.80,05.05, gen_color(255,0,100, 0), vars), "1start", &change_ui);
	button(vars, screen_pc(25.30,25.025, gen_color(255,0,100, 0), vars), "1start", &change_setting);
	slider(vars, screen_pc(25.40,25.025, gen_color(255,0,100, 0), vars), slider_param(120.0, 1.0, &vars->settings.fps_cap), 1.0);
	slider(vars, screen_pc(25.50,25.025, gen_color(255,0,100, 0), vars), slider_param(1.6, 0.2, &vars->settings.y_ratio_mouse_speed), 0.1);
	slider(vars, screen_pc(25.60,25.025, gen_color(255,0,100, 0), vars), slider_param(2.0, 0.1, &vars->settings.x_ratio_mouse_speed), 0.1);
	//slider(vars, screen_pc(25.50,25.025, gen_color(255,0,100, 0), vars), slider_param(0.2, 1.6, &vars->settings.y_ratio_mouse_speed), 0.1);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

int	frame(void *data)
{
	t_vars	*vars;
	long	temp;
	char	*fps;
	char	*itoa;

	vars = (t_vars *)data;
	if (!vars->ui)
	{
	if (!vars->settings.fps_cap || !fmod(gettime(vars->n1), (1000 / (int)vars->settings.fps_cap)))
	{
		render(vars);
		temp = gettime(vars->n1);
		itoa = ft_itoa(1000 / (temp - vars->n2));
		fps = ft_strjoin("FPS: ", itoa);
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
	fill_vars(&vars, fd);
	(void)extract_name;
	vars.rays_number = 0;
	vars.settings.fps_cap = 60;
	vars.settings.map_type = 1;
	vars.win = mlx_new_window(vars.mlx, vars.win_size.x,
			vars.win_size.y, extract_name(argv[1]));
	printf("EA: %s\nNO: %s\nSO: %s\nWE: %s\nF: %#x\nC: %#x\n",
		vars.ea, vars.no, vars.so, vars.we, to_rgb(vars.f, 0), to_rgb(vars.c, 0));
	// raycasting(&vars);
	// if (!vars.win)
	// 	esc(&vars, 1);
	//mlx_key_hook(vars.win, key_hook, &vars);
	mlx_do_key_autorepeatoff(vars.mlx);
	mlx_hook(vars.win, ON_KEYDOWN, 0, key_hook_down, &vars);
	mlx_hook(vars.win, ON_KEYUP, 0, key_hook_up, &vars);
	mlx_hook(vars.win, ON_MOUSEUP, 0, mouse_hook_up, &vars);
	mlx_hook(vars.win, ON_DESTROY, 0, test_hook, &vars);
	mlx_loop_hook(vars.mlx, frame, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	// mlx_loop_hook(vars.mlx, raycasting, &vars);
	vars.n1 = gettime(0);
	mlx_loop(vars.mlx);
	free_textures(&vars);
}
