/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:24:04 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/22 23:12:45 by arangoni         ###   ########.fr       */
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

// void	esc(t_vars *vars, int err)
// {
// 	if (vars->img.img)
// 		mlx_destroy_image(vars->mlx, vars->img.img);
// 	if (vars->win)
// 		mlx_destroy_window(vars->mlx, vars->win);
// 	if (vars->l_pts)
// 		free(vars->l_pts);
// 	if (vars->l_tmp)
// 		free(vars->l_tmp);
// 	exit(err);
// }

void	coord(t_coord *p, int x, int y, int z)
{
	p->x = x;
	p->y = y;
	p->z = z;
}

// void	pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	if (x >= 0 && x < 1920 && y >= 0 && y < 1080)
// 	{
// 		dst = data->addr + (y * data->line_length + x * data->bits_per_pixel);
// 		*(unsigned int *)dst = color;
// 	}
// }

// int	f_loop(t_vars *vars)
// {
// 	vars->rotation.z -= (1 * vars->rotate) * (vars->proj_type == 1);
// 	if (vars->color.v)
// 		vars->color = cycle_color(vars->color);
// 	if (vars->rotate || vars->color.v)
// 		project(vars);
// 	return (0);
// }
