/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:42:07 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/24 21:57:18 by arangoni         ###   ########.fr       */
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

static void	fill_vars(t_vars *vars, int fd)
{
	t_data	img;

	vars->map = parse(fd, vars);
	vars->mlx = mlx_init();
	vars->plane.x = 0.0;
	vars->plane.y = 0.66;
	vars->pos.x = 2.0;
	vars->pos.y = 2.0;
	vars->dir.x = -1.0;
	vars->dir.y = 0.0;
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

int	raycasting(t_vars *vars)
{
	int		x;
	t_ray	ray;
	double	step;
	int		y;

	x = -1;
	while (++x < vars->size.x)
	{
		ray.camera_x = 2 * x / vars->size.x - 1;
		ray.ray_dir.x = vars->dir.x + vars->plane.x * ray.camera_x;
		ray.ray_dir.y = vars->dir.y + vars->plane.y * ray.camera_x;
		ray.map_pos.x = (ft_strchr(vars->map, 'P') - vars->map) % vars->size.x;
		ray.map_pos.y = (ft_strchr(vars->map, 'P') - vars->map) / vars->size.x;
		if (ray.ray_dir.x == 0)
			ray.delta_dist.x = 1e30;
		else
			ray.delta_dist.x = fabs(1 / ray.ray_dir.x);
		if (ray.ray_dir.y == 0)
			ray.delta_dist.y = 1e30;
		else
			ray.delta_dist.y = fabs(1 / ray.ray_dir.y);
		if (ray.ray_dir.x < 0)
		{
			ray.step.x = -1;
			ray.side_dist.x = (vars->pos.x - ray.map_pos.x) * ray.delta_dist.x;
		}
		else
		{
			ray.step.x = 1;
			ray.side_dist.x = (ray.map_pos.x + 1.0 - ray.map_pos.x) * ray.delta_dist.x;
		}
		if (ray.ray_dir.y < 0)
		{
			ray.step.y = -1;
			ray.side_dist.y = (vars->pos.y - ray.map_pos.y) * ray.delta_dist.y;
		}
		else
		{
			ray.step.y = 1;
			ray.side_dist.y = (ray.map_pos.y + 1.0 - ray.map_pos.y) * ray.delta_dist.y;
		}
		ray.hit = 0;
		//printf("Next ray\n");
		while (ray.hit == 0)
		{
			if (ray.side_dist.x < ray.side_dist.y)
			{
				ray.side_dist.x += ray.delta_dist.x;
				ray.map_pos.x += ray.step.x;
				ray.side = 0;
			}
			else
			{
				ray.side_dist.y += ray.delta_dist.y;
				ray.map_pos.y += ray.step.y;
				ray.side = 1;
			}
			//printf("ray: %d %d c:%c\n", ray.map_pos.x, ray.map_pos.y, vars->map[ray.map_pos.x + ray.map_pos.y * vars->size.x]);
			if (vars->map[ray.map_pos.x + ray.map_pos.y * vars->size.x] == '1')
				ray.hit = 1;
		}
		printf("%d %d\n", ray.map_pos.x, ray.map_pos.y)
		if (ray.side == 0)
			ray.perp_wall_dist = ray.side_dist.x - ray.delta_dist.x;
		else
			ray.perp_wall_dist = ray.side_dist.y - ray.delta_dist.y;
		ray.h = ray.map_pos.y + (1 - ray.step.y) / 2;
		ray.line_height = (int)(ray.h / ray.perp_wall_dist);

		ray.pitch = 100;
		ray.draw_start = -ray.line_height / 2 + ray.h / 2 + ray.pitch;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = ray.line_height / 2 + ray.h / 2 + ray.pitch;
		if (ray.draw_end >= ray.h)
			ray.draw_end = ray.h - 1;
		if (ray.side == 0)
			ray.wall.x = ray.map_pos.y + ray.perp_wall_dist * ray.ray_dir.y;
		else
			ray.wall.x = ray.map_pos.y + ray.perp_wall_dist * ray.ray_dir.y;
		ray.wall.x -= floor((ray.wall.x));
		ray.tex.x = (int)(ray.wall.x * TEX_W);
		if (ray.side == 0 && ray.ray_dir.x > 0)
			ray.tex.x = TEX_W - ray.tex.x - 1;
		if (ray.side == 1 && ray.ray_dir.y < 0)
			ray.tex.x = TEX_W - ray.tex.x - 1;
		step = 1.0 * TEX_W / ray.line_height;
		ray.tex_pos = (ray.draw_start - ray.pitch - ray.h / 2 + ray.line_height / 2) * step;
		y = ray.draw_start - 1;
		printf("%d %d\n", x, y);
		while (++y < ray.draw_end)
		{
			ray.tex.y = (int)ray.tex_pos & (TEX_W - 1);
			ray.tex_pos += step;
			ray.color = 0xffffff;
			//ray.color = vars->textures_img[ft_atoi(vars->map[ray.map_pos.x + ray.map_pos.y * vars->size.x])].addr[]//TODO addresse pixel textures
			// if (ray.side == 1)
			// 	ray.color = ray.color >> 1 & 8355711;
			pixel_put(&vars->img, x, y, ray.color);
			//mlx_pixel_put(vars->mlx, vars->win, x, y, ray.color);
			printf("%d %d", x, y);
		}	
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
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
	(void)extract_name;
	vars.win = mlx_new_window(vars.mlx, 1920,
			1080, extract_name(argv[1]));
	printf("EA: %s\nNO: %s\nSO: %s\nWE: %s\n", vars.textures.ea, vars.textures.no, vars.textures.so, vars.textures.we);
	printf("%s\n", vars.map);
	raycasting(&vars);

	// if (!vars.win)
	// 	esc(&vars, 1);
	//mlx_hook(vars.win, 2, 0, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, test_hook, &vars);
	//mlx_mouse_hook(vars.win, mouse_hook, &vars);
	//project(&vars);
	printf("List\n%s\n", vars.map);
	mlx_loop_hook(vars.mlx, raycasting, &vars);
	mlx_loop(vars.mlx);
}
