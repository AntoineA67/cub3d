/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:03:35 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/13 11:35:34 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

unsigned int	add_shade(t_vars *v, unsigned int c, unsigned int di, double ao)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	(void)v;
	di += ao * 255;
	if (di > 255)
		di = 255;
	r = (c >> 16) & 0xff;
	g = (c >> 8) & 0xff;
	b = c & 0xff;
	return ((((r > di) * (r - di)) << 16)
		+ (((g > di) * (g - di) << 8))
		+ (b > di) * (b - di));
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
