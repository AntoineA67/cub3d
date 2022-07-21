/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:20:59 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/25 14:33:06 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_easy_texture(t_vars *vars, t_coord p, t_data *img)
{
	int		dy;
	int		dx;
	double	ratio_x;
	double	img_x;
	double	img_y;

	if (!p.z)
		return ;
	img_y = 0;
	ratio_x = (img->size.x + .0) / (p.z + .0);
	dy = p.y - p.z / 2;
	while (++dy < p.y + p.z / 2)
	{
		dx = p.x - p.z / 2;
		img_x = 0;
		while (++dx < p.x + p.z / 2 && img_x < img->size.x && img_y >= 0
			&& img_x >= 0 && img_y < img->size.y && is_in_window(vars, dx, dy))
		{
			pixel_put(vars->img, dx, dy, *(unsigned int *)(img->addr
					+ ((int)((int)img_x * (img->bits_per_pixel / 8))
						+ (int)((int)img_y * img->line_length))));
			img_x += ratio_x;
		}
		img_y += (img->size.y + .0) / (p.z + .0);
	}
}

void	draw_square_texture_center(t_vars *v, t_coord p, t_data *img)
{
	int		dy;
	int		dx;
	double	img_x;
	double	img_y;

	if (!p.z)
		return ;
	img_y = 0;
	dy = p.y - p.z / 2;
	while (++dy < p.y + p.z / 2)
	{
		dx = p.x - p.z / 2;
		img_x = 0;
		while (++dx < p.x + p.z / 2 && img_x < img->size.x && img_y >= 0
			&& img_x >= 0 && img_y < img->size.y
			&& is_in_window(v, dx, dy - v->player.rot.y))
		{
			pixel_put(v->img, dx, dy - v->player.rot.y,
				*(unsigned int *)(img->addr + ((int)((int)img_x
							* (img->bits_per_pixel / 8))
						+ (int)((int)img_y * img->line_length))));
			img_x += (img->size.x + .0) / (p.z + .0);
		}
		img_y += (img->size.y + .0) / (p.z + .0);
	}
}

void	draw_square(t_vars *vars, t_coord p)
{
	int	dy;
	int	dx;

	dy = p.y;
	while (++dy < p.y + p.z)
	{
		dx = p.x;
		while (++dx < p.x + p.z)
			if (is_in_window(vars, dx, dy))
				pixel_put(vars->img, dx,
					dy, to_rgb(p.c, 0));
	}
}

void	draw_square_center(t_vars *vars, t_coord p)
{
	int	dy;
	int	dx;

	dy = p.y - p.z / 2;
	while (++dy < p.y + p.z / 2)
	{
		dx = p.x - p.z / 2;
		while (++dx < p.x + p.z / 2)
			if (is_in_window(vars, dx, dy))
				pixel_put(vars->img, dx,
					dy, to_rgb(p.c, 0));
	}
}

double	dist(double ax, double ay, double bx, double by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}
