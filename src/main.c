/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:42:07 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/30 16:33:40 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// static t_coord	*cp_l_pts(t_coord *l_pts)
// {
// 	t_coord	*mod_l_pts;
// 	int		i;

// 	mod_l_pts = ft_calloc(l_pts[0].z + 1, sizeof(t_coord));
// 	if (!mod_l_pts)
// 	{
// 		free(l_pts);
// 		exit(EXIT_FAILURE);
// 	}
// 	i = -1;
// 	while (++i < l_pts[0].z + 1)
// 	{
// 		mod_l_pts[i].x = l_pts[i].x;
// 		mod_l_pts[i].y = l_pts[i].y;
// 		mod_l_pts[i].z = l_pts[i].z;
// 		mod_l_pts[i].c.r = l_pts[i].c.r;
// 		mod_l_pts[i].c.g = l_pts[i].c.g;
// 		mod_l_pts[i].c.b = l_pts[i].c.b;
// 		mod_l_pts[i].c.v = l_pts[i].c.v;
// 	}
// 	return (mod_l_pts);
// }

int	init_player(t_vars *vars)
{
	char	*player_in_map;

	vars->player.rot = vars->start_rot;
	vars->player.delta.x = 0;
	vars->player.delta.y = 0;
	player_in_map = ft_strchr(vars->map, 'P');
	vars->map[player_in_map - vars->map] = '0';
	vars->player.pos.x = ((player_in_map - vars->map) % vars->size.x) * vars->min_map_mult;
	vars->player.pos.y = ((player_in_map - vars->map) / vars->size.x) * vars->min_map_mult;
	return (0);
}

void	init_imgs(t_vars *vars)
{
	mlx_xpm_file_to_image(vars->mlx, vars->textures.no, &vars->textures.img_no.size.x, &vars->textures.img_no.size.y);
}

static void	fill_vars(t_vars *vars, int fd)
{
	t_data	img;

	vars->win_size.x = 1920;
	vars->win_size.y = 1080;
	vars->map = parse(fd, vars);
	if (init_player(vars))
		return ; //NO PLAYER IN MAP
	init_imgs(vars);
	vars->mlx = mlx_init();
	vars->plane.x = 0.0;
	vars->plane.y = 0.66;
	img.img = mlx_new_image(vars->mlx, vars->win_size.x, vars->win_size.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	 		&img.line_length, &img.endian);
	if (!img.addr)
		return ;
	img.bits_per_pixel /= 8;
	vars->img = img;
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

void	change_ui(void		*v, void	*data)
{
	t_vars	*vars;

	vars = (t_vars *)v;
	vars->ui = *((int*)data);
}

void	change_setting(void		*v, void	*dat)
{
	t_vars	*vars;
	int	data;

	data = *((int*)dat);
	vars = (t_vars *)v;
	if (data == 1)
	{
		vars->settings.map_type++;
		if (vars->settings.map_type == 3)
			vars->settings.map_type = 0;
	}
}

void	button(t_vars *vars, t_coords p, char *txt,void (*f)(void*, void*))
{
	int	dy;
	int	dx;
	int	data;

	dy = p.a.y;
	data = (int)(*txt - '0');
	while (++dy < p.b.y)
	{
		dx = p.a.x;
		while (++dx < p.b.x)
			pixel_put(&vars->img, dx,
					dy, to_rgb(p.a.c, 0));
	}
	(void)txt;
	//printf("%d\n", mlx_string_put(vars->mlx, vars->win,100,100,0xff00ff, "PLAY"));
	if (vars->clicked)
	{
		if (vars->clicked_co.x >= p.a.x && vars->clicked_co.x <= p.b.x)
			if (vars->clicked_co.y >= p.a.y && vars->clicked_co.y <= p.b.y)
				f(vars, &data);
	}
}

t_coords screen_pc(double off, double wh, t_rgb colore, t_vars *vars)
{
	t_coords res;
	int	width;
	int	height;
	int	off_l;
	int	off_d;

	width = (int)wh;
	height = fmod(wh * 100.0, 100.0);
	off_l = (int)off;
	off_d = fmod(off * 100.0, 100.0);
	res.a.x = vars->win_size.x * off_l / 100;
	res.a.y = vars->win_size.y * off_d / 100;
	res.b.x = res.a.x + (vars->win_size.x * width / 100);
	res.b.y = res.a.y + (vars->win_size.x * height / 100);
	res.a.c = colore;
	//printf("%d|%d|%d\n", res.x, res.y, res.z);
	return (res);
}

int	ui_frame1(t_vars	*vars)
{ 
	button(vars, screen_pc(25.15,50.05, gen_color(255,0,100, 100), vars), "0Play", &change_ui);
	button(vars, screen_pc(25.30,25.025, gen_color(255,255,100, 0), vars), "2Maps", &change_ui);
	button(vars, screen_pc(25.40,25.025, gen_color(25,60,100, 0), vars), "3TexturePack", &change_ui);
	button(vars, screen_pc(25.50,25.025, gen_color(56,69,10, 0), vars), "4Parameter", &change_ui);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

int	ui_frame2(t_vars	*vars)
{ 
	button(vars, screen_pc(80.80,05.05, gen_color(255,0,100, 0), vars), "1Return", &change_ui);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}
int	ui_frame3(t_vars	*vars)
{ 
	button(vars, screen_pc(80.80,05.05, gen_color(255,0,100, 0), vars), "1Return", &change_ui);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}
int	ui_frame4(t_vars	*vars)
{ 
	button(vars, screen_pc(80.80,05.05, gen_color(255,0,100, 0), vars), "1Return", &change_ui);
	button(vars, screen_pc(25.30,25.025, gen_color(255,0,100, 0), vars), "1Change_minimap", &change_setting);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
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

int	frame(void *data)
{
	t_vars	*vars;
	long	temp;
	char	*fps;
	char	*itoa;

	vars = (t_vars *)data;
	if (!vars->ui)
	{
	if (!vars->settings.fps_cap || !(gettime(vars->n1) % (1000 / vars->settings.fps_cap)))
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
			ft_int_memset(vars->img.addr, 0x000000,
		vars->img.line_length * vars->win_size.y / 4);
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
		ui_frame4(vars);
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
	vars.plane_rays = ft_calloc(sizeof(t_vector2), vars.rays_number);
	vars.settings.fps_cap = 144;
	vars.win = mlx_new_window(vars.mlx, vars.win_size.x,
			vars.win_size.y, extract_name(argv[1]));
	printf("EA: %s\nNO: %s\nSO: %s\nWE: %s\nF: %#x\nC: %#x\n",
		vars.textures.ea, vars.textures.no, vars.textures.so, vars.textures.we, to_rgb(vars.textures.f, 0), to_rgb(vars.textures.c, 0));
	// raycasting(&vars);
	// if (!vars.win)
	// 	esc(&vars, 1);
	mlx_hook(vars.win, 2, 0, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, test_hook, &vars);
	mlx_loop_hook(vars.mlx, frame, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	//project(&vars);
	// mlx_loop_hook(vars.mlx, raycasting, &vars);
	vars.n1 = gettime(0);
	mlx_loop(vars.mlx);
}
