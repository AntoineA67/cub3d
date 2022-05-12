/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:24:04 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/11 18:31:05 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// void	reset(t_vars *vars)
// {
// 	vars->zoom = 10;
// 	coord(&vars->rotation, -55, 0, -45);
// 	vars->rotate = 0;
// 	vars->color.v = 0;
// 	color(&vars->color, 255, 255, 255);
// 	coord(&vars->translate, vars->size.x / 2, vars->size.y / 2, 0);
// }

void	esc(t_vars *vars, int err)
{
	if (err)
		write(2, "Error\n", 6);
	if (vars->img->img)
		mlx_destroy_image(vars->mlx, vars->img->img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	exit(err);
}

t_coord	coord(t_coord *p, int x, int y, int z)
{
	p->x = x;
	p->y = y;
	p->z = z;
	return (*p);
}

t_coord	gen_coord(int x, int y, int z, t_rgb c)
{
	t_coord p;
	p.x = x;
	p.y = y;
	p.z = z;
	p.c.r = c.r;
	p.c.g = c.g;
	p.c.b = c.b;
	p.c.v = c.v;
	return (p);
}

void	pixel_put(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	// if (x >= 0 && x < 1920 && y >= 0 && y < 1080)
	// {
	if (color>>24 != 255)
	{
		dst = data->addr + (y * data->line_length + x * data->bits_per_pixel);
		*(unsigned int *)dst = color;
	}
	// else
		// printf("aa\n");
	// }
}

// int	f_loop(t_vars *vars)
// {
// 	vars->rotation.z -= (1 * vars->rotate) * (vars->proj_type == 1);
// 	if (vars->color.v)
// 		vars->color = cycle_color(vars->color);
// 	if (vars->rotate || vars->color.v)
// 		project(vars);
// 	return (0);
// }
