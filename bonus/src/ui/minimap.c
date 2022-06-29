/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:11:59 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/29 13:26:30 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	show_player(t_vars *vars)
{
	draw_square_center(vars, gen_coord((200) / 2,
			(200) / 2, 16 / 2.0, gen_color(255, 0, 100, 0)));
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
