/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:55:44 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/13 16:26:07 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ui_frame1(t_vars	*vars)
{
	button(screen_pc(25.15, 50.1, gen_color(255, 0, 100, 100), vars),
		"start", &change_ui, 0);
	button(screen_pc(25.30, 25.05, gen_color(255, 255, 100, 0), vars),
		"maps", &change_ui, 2);
	button(screen_pc(25.40, 25.05, gen_color(25, 60, 100, 0), vars),
		"textures", &change_ui, 3);
	button(screen_pc(25.50, 25.05, gen_color(56, 69, 10, 0), vars),
		"settings", &change_ui, 4);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

int	ui_frame2(t_vars	*v)
{
	int		fd;
	char	*str;
	double	off;
	int		i;

	fd = open("maps.txt", O_RDONLY);
	str = ft_strdup("MAPS:");
	off = 30.10;
	i = -1;
	while (v->scroll && i++ < v->scroll)
	{
		free(str);
		str = get_next_line(fd);
	}
	while (str && off < 31.0)
	{
		if (i >= 0)
			button(screen_pc(off, 20.025, gen_color(0, 0, 0, 255), v),
				NULL, &change_map, i);
		img_text(v, str, screen_pc(off, 20.025, gen_color(255, 0, 100, 0), v));
		off += 0.10 + (0 * i++);
		free(str);
		str = get_next_line(fd);
	}
	while (str)
	{
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close(fd);
	button(screen_pc(80.80, 05.05, gen_color(255, 0, 100, 0), v),
		"start", &change_ui, 1);
	mlx_put_image_to_window(v->mlx, v->win, v->img->img, 0, 0);
	return (0);
}

int	ui_frame3(t_vars	*v)
{
	t_rgb	grey;
	t_rgb	red;

	grey = gen_color(20, 20, 20, 0);
	red = gen_color(255, 255, 100, 0);
	button(screen_pc(5.10, 05.05, grey, v), NULL, &set_text, 0);
	button(screen_pc(5.10, 05.05, grey, v), NULL, &change_ui, 5);
	img_text(v, "north", screen_pc(5.15, 10.10, red, v));
	button(screen_pc(20.10, 05.05, grey, v), NULL, &set_text, 1);
	button(screen_pc(20.10, 05.05, grey, v), NULL, &change_ui, 5);
	img_text(v, "south", screen_pc(20.15, 10.10, red, v));
	button(screen_pc(40.10, 05.05, grey, v), NULL, &set_text, 2);
	button(screen_pc(40.10, 05.05, grey, v), NULL, &change_ui, 5);
	img_text(v, "east", screen_pc(40.15, 10.10, red, v));
	button(screen_pc(60.10, 05.05, grey, v), NULL, &set_text, 3);
	button(screen_pc(60.10, 05.05, grey, v), NULL, &change_ui, 5);
	img_text(v, "west", screen_pc(60.15, 10.10, red, v));
	button(screen_pc(80.10, 05.05, grey, v), NULL, &set_text, 4);
	button(screen_pc(80.10, 05.05, grey, v), NULL, &change_ui, 5);
	img_text(v, "Ennemis", screen_pc(80.15, 10.10, red, v));
	button(screen_pc(80.80, 05.05, grey, v), "start", &change_ui, 1);
	mlx_put_image_to_window(v->mlx, v->win, v->img->img, 0, 0);
	return (0);
}
