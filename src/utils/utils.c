/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:24:04 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/10 17:49:25 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	exit_err(t_vars *vars, int err)
{
	if (err)
		write(2, "Error\n", 6);
	if (vars->img->img)
		mlx_destroy_image(vars->mlx, vars->img->img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->textures)
		free_textures(vars);
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
	t_coord	p;

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

	if (x >= 0 && x < 1920 && y >= 0 && y < 1080 && color >> 24 != 255)
	{
		dst = data->addr + (y * data->line_length + x * data->bits_per_pixel);
		*(unsigned int *)dst = color;
	}
}

void	pixel_put_add(t_data *data, int *x, int *y, unsigned int *color)
{
	char	*dst;

	dst = data->addr + (*y * data->line_length + *x * data->bits_per_pixel);
	*(unsigned int *)dst = *color;
}
