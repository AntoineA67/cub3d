/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:03:35 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/07 16:23:20 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	is_in_window(t_vars *vars, int x, int y)
{
	return (x >= 0
		&& x < vars->win_size.x
		&& y >= 0
		&& y < vars->win_size.y);
}

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
		pixel_put((vars->img), p1.x, p1.y, to_rgb(p1.c, 0));
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

unsigned int	add_shade(t_vars *vars, unsigned int c, unsigned int dist_int, double ao)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	(void)vars;
	(void)c;
	(void)ao;
	r = (c>>16) + (int)(255 * ao) & 0xff;
	g = (c>>8) + (int)(255 * ao) & 0xff;
	b = c + (int)(255 * ao) & 0xff;
	// return ((((r))<<16)
	// 	+ (((g)<<8))
	// 	+ (b));
	// printf("%d %d %d\n", r, g, b);
	// return ((dist_int<<16) + (dist_int<<8) + dist_int);
	return ((((r > dist_int) * (r - dist_int))<<16)
		+ (((g > dist_int) * (g - dist_int)<<8))
		+ (b > dist_int) * (b - dist_int));
}

void	vert_line(t_vars *vars, int x, int size, int color)
{
	int	i;

	if (x == vars->win_size.x / 2)
	printf("%d\n", size);
	i = vars->win_size.y / 2 - size / 2 - 1;
	while (++i < vars->win_size.y / 2 + size / 2)
		pixel_put(vars->img, x, i, color);
}


void	line_texture(t_vars *vars, int screen_x, int img_x, t_data *img, double hit_dist, double ao)
{
	int				i;
	double			y;
	double			step;
	double			wall_height;
	int				draw_end;
	double			ao_vert;

	wall_height = vars->win_size.y / 2 / hit_dist * .90;
	if (wall_height < 2)
		wall_height = 0;
	if (screen_x == vars->win_size.x / 2)
		printf("%.2f\n", ao);
	// 	printf("%.2f %.2f\n", wall_height, hit_dist);
	y = 0.0;
	i = vars->win_size.y / 2 - wall_height - vars->player.rot.y;
	step = (img->size.y * 1.0) / ((vars->win_size.y / 2 + wall_height)
			- (vars->win_size.y / 2 - wall_height));
	if (i < 0)
	{
		y = step * (-i);
		i = 0;
	}
	draw_end = vars->win_size.y / 2 + wall_height - vars->player.rot.y;
	if (draw_end > vars->win_size.y)
		draw_end = vars->win_size.y;
	if (img_x < 0)
		img_x = 0;
	if (y < 0.0)
		y = 0.0;
	(void)ao_vert;
	while (++i < draw_end && (int)y < img->size.y && img_x < img->size.x)
	{
		// if (y < 0.1)
		// 	printf("%.2f %.2f\n", y / img->size.y, sin((y / img->size.y) * M_PI));
		pixel_put(vars->img, screen_x, i,
			add_shade(vars, *(unsigned int *)(img->addr + (img_x
			* (img->bits_per_pixel / 8) + (int)y * img->line_length)), (int)(hit_dist * 10.0),
			(((fabs(1.0 - ao) > .1) * (1.0 - ao) - 1.0) * .5
			+ (sin((((y + 1) / (img->size.y + 1))) * M_PI)) * .5) * (1 - 1 / hit_dist)));
			// sin((((y + 1) / (img->size.y + 1))) * M_PI) & 
		y += step;
	}
}
