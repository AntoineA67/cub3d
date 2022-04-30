/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:42:07 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/30 15:00:16 by arangoni         ###   ########.fr       */
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
	t_textures	*imgs;

	imgs = &vars->textures;
	imgs->img_no.img = mlx_xpm_file_to_image(vars->mlx, imgs->no, &imgs->img_no.size.x,
		&imgs->img_no.size.y);
	imgs->img_no.addr = mlx_get_data_addr(imgs->img_no.img, &imgs->img_no.bits_per_pixel,
		&imgs->img_no.line_length, &imgs->img_no.endian);
	imgs->img_so.img = mlx_xpm_file_to_image(vars->mlx, imgs->so, &imgs->img_so.size.x,
		&imgs->img_so.size.y);
	imgs->img_so.addr = mlx_get_data_addr(imgs->img_so.img, &imgs->img_so.bits_per_pixel,
		&imgs->img_so.line_length, &imgs->img_so.endian);
	imgs->img_ea.img = mlx_xpm_file_to_image(vars->mlx, imgs->ea, &imgs->img_ea.size.x,
		&imgs->img_ea.size.y);
	imgs->img_ea.addr = mlx_get_data_addr(imgs->img_ea.img, &imgs->img_ea.bits_per_pixel,
		&imgs->img_ea.line_length, &imgs->img_ea.endian);
	imgs->img_we.img = mlx_xpm_file_to_image(vars->mlx, imgs->we, &imgs->img_we.size.x,
		&imgs->img_we.size.y);
	imgs->img_we.addr = mlx_get_data_addr(imgs->img_we.img, &imgs->img_we.bits_per_pixel,
		&imgs->img_we.line_length, &imgs->img_we.endian);
}

static void	fill_vars(t_vars *vars, int fd)
{
	t_data	img;

	vars->mlx = mlx_init();
	vars->win_size.x = 1920;
	vars->win_size.y = 1080;
	vars->map = parse(fd, vars);
	if (init_player(vars))
		return ; //NO PLAYER IN MAP
	init_imgs(vars);
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
	if (!vars->fps_cap || !(gettime(vars->n1) % (1000 / vars->fps_cap)))
	{
		render(vars);
		temp = gettime(vars->n1);
		itoa = ft_itoa(1000 / (temp - vars->n2));
		fps = ft_strjoin("FPS: ", itoa);
		mlx_string_put(vars->mlx, vars->win, 100, 100, 0xff, fps);
		free(itoa);
		free(fps);
		vars->n2 = temp;
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
	fill_vars(&vars, fd);
	(void)extract_name;
	vars.rays_number = 0;
	vars.plane_rays = ft_calloc(sizeof(t_vector2), vars.rays_number);
	vars.render_dist = 30;
	vars.fps_cap = 144;
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
	// mlx_mouse_hook(vars.win, mouse_hook, &vars);
	//project(&vars);
	// mlx_loop_hook(vars.mlx, raycasting, &vars);
	vars.n1 = gettime(0);
	mlx_loop(vars.mlx);
}
