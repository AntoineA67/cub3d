/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:03:35 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/30 14:26:25 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// int	is_in_window(t_coord *point)
// {
// 	return (point->x >= 0
// 		&& point->x < 1920
// 		&& point->y >= 0
// 		&& point->y < 1080);
// }

static void	fill_line_struct(t_line *l, t_coord *p1, t_coord *p2)
{
	l->dx = ft_abs(p2->x - p1->x);
	l->dy = -ft_abs(p2->y - p1->y);
	if (p1->x < p2->x)
		l->sx = 1;
	else
		l->sx = -1;
	if (p1->y < p2->y)
		l->sy = 1;
	else
		l->sy = -1;
	l->err = l->dx + l->dy;
	l->dist = l->dx * l->dx + l->dy * l->dy;
}

// int	base_color(t_rgb *c1, t_rgb *c2, float val, t_rgb map_color)
// {
// 	(void)c1;
// 	(void)c2;
// 	(void)val;
// 	return (0x00 << 24 | map_color.r << 16
// 		| map_color.g << 8 | map_color.b);
// }

// int	grad_color(t_rgb *c1, t_rgb *c2, float val, t_rgb map_color)
// {
// 	t_rgb	color;

// 	(void)map_color;
// 	color.r = c1->r + (c2->r - c1->r) * val;
// 	color.g = c1->g + (c2->g - c1->g) * val;
// 	color.b = c1->b + (c2->b - c1->b) * val;
// 	return (to_rgb(color));
// }

void	plot_line(t_vars *vars, t_coord p1, t_coord p2)
{
	t_line	l;
	int		i;

	fill_line_struct(&l, &p1, &p2);
	i = 0;
	while (++i)
	{
		pixel_put(&(vars->img), p1.x, p1.y, to_rgb(p1.c, 0));
		l.e_d = 2 * l.err;
		if (l.e_d >= l.dy)
		{
			if (p1.x == p2.x)
				break ;
			l.err += l.dy;
			p1.x += l.sx;
		}
		if (l.e_d <= l.dx)
		{
			if (p1.y == p2.y)
				break ;
			l.err += l.dx;
			p1.y += l.sy;
		}
	}
}

void	line_texture(t_vars *vars, int screen_x, int img_x, double dist, t_data *img)
{
	int		i;
	double	y;
	double	step;

	i = vars->win_size.y / 2 - (int)(10000 / dist) - 1;
	y = 0.0;
	step = (img->size.y * 1.0) / ((vars->win_size.y / 2 + (int)(10000 / dist))
			- (vars->win_size.y / 2 - (int)(10000 / dist))) - .1;
	printf("%d %d %f %d\n", i, vars->win_size.y / 2 + (int)(10000 / dist),
		step, img->size.y);
	while (++i < vars->win_size.y / 2 + (int)(10000 / dist))
	{
		// printf("%d %d %d %.2f\n", screen_x, i, (int)y, y);
		pixel_put(&vars->img, screen_x, i,
			*(unsigned int *)(img->addr + (img_x
			* (img->bits_per_pixel / 8) + (int)y * img->line_length)));
		y += step;
	}
}
