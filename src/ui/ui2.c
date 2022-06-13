/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:40:29 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/13 10:55:55 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ui_texture(t_vars	*v)
{
	int		fd;
	char	*str;
	double	off;
	int		i;

	fd = open("textures.txt", O_RDONLY);
	str = "         TEXTURES:";
	off = 30.10;
	i = -1;
	while (v->scroll && i++ < v->scroll)
		str = get_next_line(fd);
	while (str && off < 31.0)
	{
		if (i >= 0)
			button(screen_pc(off, 20.025, gen_color(0, 0, 0, 255), v),
				NULL, &change_texture, i);
		img_text(v, str + 9, screen_pc(off, 20.025, gen_color(255, 0, 100, 0), v));
		off += 0.10 + (0 * i++);
		str = get_next_line(fd);
	}
	close(fd);
	button(screen_pc(80.80, 05.05, gen_color(255, 0, 100, 0), v),
		"start", &change_ui, 1);
	mlx_put_image_to_window(v->mlx, v->win, v->img->img, 0, 0);
	return (0);
}

int	ui_setting(t_vars	*vars)
{
	t_rgb	color;

	color = gen_color(255, 0, 100, 0);
	draw_2d_map(vars, vars->min_map_mult);
	button(screen_pc(80.80, 05.05, color, vars), "start", &change_ui, 1);
	button(screen_pc(25.30, 25.025, color, vars), "start", &change_setting, 1);
	img_text(vars, ft_strjoin("Minimaps_type: ", ft_itoa(vars->settings.map_type)),
		screen_pc(60.30, 20.025, color, vars));
	slider(vars, screen_pc(25.40, 25.025, color, vars),
		slider_param(120.0, 0, &vars->settings.fps_cap, 1.0));
	img_text(vars, ft_strjoin("FPS_CAPS: ", ft_itoa(vars->settings.fps_cap)),
		screen_pc(60.40, 20.025, color, vars));
	slider(vars, screen_pc(25.50, 25.025, color, vars),
		slider_param(1.6, 0.2, &vars->settings.y_ratio_mouse_speed, 0.1));
	img_text(vars, ft_strjoin("Sensibilite Y: ", ft_dtoa(vars->settings.y_ratio_mouse_speed)),
		screen_pc(60.50, 20.025, color, vars));
	slider(vars, screen_pc(25.60, 25.025, color, vars),
		slider_param(2.0, 0.1, &vars->settings.x_ratio_mouse_speed, 0.1));
	img_text(vars, ft_strjoin("Sensibilite X: ", ft_dtoa(vars->settings.x_ratio_mouse_speed)),
		screen_pc(60.60, 20.025, color, vars));
	slider(vars, screen_pc(25.70, 25.025, color, vars),
		slider_param(7.0, 0.0, &vars->settings.m, 1.0));
	img_text(vars, ft_strjoin("M: ", ft_dtoa(vars->settings.m)),
		screen_pc(60.70, 20.025, color, vars));
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}