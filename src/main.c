/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:42:07 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/28 18:19:53 by arangoni         ###   ########.fr       */
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

	vars->player.rot = 0; //TODO changer selon orientation de depart
	vars->player.delta.x = 0;
	vars->player.delta.y = 0;
	player_in_map = ft_strchr(vars->map, 'P');
	vars->map[player_in_map - vars->map] = '0';
	vars->player.pos.x = (player_in_map - vars->map) % vars->size.x * 64;
	vars->player.pos.y = (player_in_map - vars->map) / vars->size.x * 64;
	return (0);
}

static void	fill_vars(t_vars *vars, int fd)
{
	t_data	img;

	vars->map = parse(fd, vars);
	if (init_player(vars))
		return ; //NO PLAYER IN MAP
	vars->mlx = mlx_init();
	vars->plane.x = 0.0;
	vars->plane.y = 0.66;
	img.img = mlx_new_image(vars->mlx, 1920, 1080);
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

void	calculate_plane_points(t_vars *vars)
{
	t_vector2	perp;

	perp = vars->player.pos;
	perp.x += cos(vars->player.rot);
	perp.y += sin(vars->player.rot);
	pixel_put(&vars->img, perp.x, perp.y, 0x0000ff);
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
	fill_vars(&vars, fd);
	(void)extract_name;
	vars.win = mlx_new_window(vars.mlx, 1920,
			1080, extract_name(argv[1]));
	printf("EA: %s\nNO: %s\nSO: %s\nWE: %s\n", vars.textures.ea, vars.textures.no, vars.textures.so, vars.textures.we);
	// raycasting(&vars);
	// if (!vars.win)
	// 	esc(&vars, 1);
	mlx_hook(vars.win, 2, 0, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, test_hook, &vars);
	render(&vars);
	// mlx_mouse_hook(vars.win, mouse_hook, &vars);
	//project(&vars);
	// mlx_loop_hook(vars.mlx, raycasting, &vars);
	mlx_loop(vars.mlx);
}
