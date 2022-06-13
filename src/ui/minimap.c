/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:11:59 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/13 12:18:41 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	show_player(t_vars *vars, double size)
{
	size = 16.0;
	if (vars->settings.map_type == 1 || vars->settings.map_type == 2)
	{
		if (vars->settings.map_type == 2)
			size = vars->win_size.x / (vars->size.x + 1);
		draw_square_center(vars, gen_coord(size * (vars->player.pos.x + 1),
				size * (vars->player.pos.y + 1), size / 2.0,
				gen_color(255, 0, 100, 0)));
		plot_line(vars,
			gen_coord(size * (vars->player.pos.x + 1), size
				* (vars->player.pos.y + 1), 0, gen_color(255, 0, 100, 0)),
			gen_coord((size * (vars->player.pos.x + 1)) + vars->player.delta.x
				* 10.0, (size * (vars->player.pos.y + 1)) + vars->player.delta.y
				* 10.0, 0, gen_color(255, 0, 100, 0)));
	}
	else
	{
		draw_square_center(vars, gen_coord((200) / 2,
				(200) / 2, size / 2.0, gen_color(255, 0, 100, 0)));
		plot_line(vars,
			gen_coord((200) / 2, (200) / 2, 0, gen_color(255, 0, 100, 0)),
			gen_coord(200 / 2 + vars->player.delta.x * 10.0, 200 / 2
				+ vars->player.delta.y * 10.0, 0, gen_color(255, 0, 100, 0)));
	}
}

int	draw_mini_circle(t_vars *v, int x, int y, t_data *i)
{
	double	pos;

	while (++y < 200)
	{
		x = -1;
		while (++x < 200)
		{
			if (sqrt(pow(x - 100, 2) + pow(y - 100, 2)) < 100)
			{
				pos = (int)(v->player.pos.y + y * 8. / 200. - 4.) * v->size.x;
				pos += (v->player.pos.x + ((x * 8.0) / 200.0) - 4.0);
				if ((int)pos > v->size.x * v->size.y || (int)pos < 0)
					pixel_put(i, x, y, to_rgb(gen_color(100, 100, 100, 0), 0));
				else if (v->map[(int)pos] == '1')
					pixel_put(i, x, y, to_rgb(gen_color(255, 255, 255, 0), 99));
				else if (v->map[(int)floor(pos)] == 'C')
					pixel_put(i, x, y, to_rgb(gen_color(0, 255, 0, 0), 0));
				else if (v->map[(int)floor(pos)] == '0')
					pixel_put(i, x, y, to_rgb(gen_color(0, 0, 0, 0), 0));
				else
					pixel_put(i, x, y, to_rgb(gen_color(100, 100, 100, 0), 0));
			}
		}
	}
	return (1);
}

void	draw_2d_map(t_vars *vars, int size)
{
	int	x;
	int	y;
	int	pos;

	y = -1;
	pos = -1;
	size = 16;
	if (vars->settings.map_type == 2)
		size = vars->win_size.x / (vars->size.x + 1);
	if (vars->settings.map_type == 0 && draw_mini_circle(vars, 0, -1, vars->img))
		return ;
	while (++y < vars->size.y)
	{
		x = -1;
		while (++x < vars->size.x && ++pos >= 0)
		{
			if (vars->map[pos] == '0')
				draw_square(vars, gen_coord(x * size + size, y * size + size, size,
						gen_color(100, 100, 100, 0)));
			else if (vars->map[pos] == '1')
				draw_square(vars, gen_coord(x * size + size, y * size + size, size,
						gen_color(200, 200, 200, 0)));
			else if (vars->map[pos] == 'O' || vars->map[pos] == 'C')
				draw_square(vars, gen_coord(x * size + size, y * size + size, size,
						gen_color(150, 20, 150, 0)));
		}
	}
}
