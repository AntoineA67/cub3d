/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:42:07 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/22 23:01:11 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static t_coord	*cp_l_pts(t_coord *l_pts)
{
	t_coord	*mod_l_pts;
	int		i;

	mod_l_pts = ft_calloc(l_pts[0].z + 1, sizeof(t_coord));
	if (!mod_l_pts)
	{
		free(l_pts);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < l_pts[0].z + 1)
	{
		mod_l_pts[i].x = l_pts[i].x;
		mod_l_pts[i].y = l_pts[i].y;
		mod_l_pts[i].z = l_pts[i].z;
		mod_l_pts[i].c.r = l_pts[i].c.r;
		mod_l_pts[i].c.g = l_pts[i].c.g;
		mod_l_pts[i].c.b = l_pts[i].c.b;
		mod_l_pts[i].c.v = l_pts[i].c.v;
	}
	return (mod_l_pts);
}

static void	fill_vars(t_vars *vars, int fd)
{
	// t_data	img;

	vars->map = parse(fd);
	// vars->l_tmp = cp_l_pts(vars->l_pts);
	// vars->mlx = mlx_init();
	// if (!vars->mlx)
	// 	esc(vars, 1);
	// coord(&vars->size, 1920, 1080, 0);
	// img.img = mlx_new_image(vars->mlx, vars->size.x, vars->size.y);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	// 		&img.line_length, &img.endian);
	// if (!img.addr)
	// 	esc(vars, 1);
	// img.bits_per_pixel /= 8;
	// vars->zoom = 10;
	// vars->rotate = 0;
	// coord(&vars->translate, vars->size.x / 2, vars->size.y / 2, 0);
	// vars->img = img;
	// coord(&vars->rotation, -55, 0, -45);
	// color(&vars->color, 255, 255, 255);
	// vars->color.v = 0;
	// vars->f = &grad_color;
	// vars->proj_type = 1;
	(void)vars;
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
	esc(vars, 0);
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
	fill_vars(&vars, fd);
	vars.win = mlx_new_window(vars.mlx, vars.size.x,
			vars.size.y, extract_name(argv[1]));
	if (!vars.win)
		esc(&vars, 1);
	//mlx_hook(vars.win, 2, 0, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, test_hook, &vars);
	//mlx_mouse_hook(vars.win, mouse_hook, &vars);
	//project(&vars);
	printf("%s", vars.map);
	mlx_loop_hook(vars.mlx, f_loop, &vars);
	mlx_loop(vars.mlx);
}
