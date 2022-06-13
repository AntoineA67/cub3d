/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:24:43 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/13 10:57:22 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_slider	slider_param(double max, double min, void *setting, double pas)
{
	t_slider	res;

	res.min = min;
	res.max = max;
	res.setting = setting;
	res.pas = pas;
	return (res);
}

void	slider_test(t_vars *vars, t_slider slider, t_coords p, double diffx)
{
	double	new;

	if (vars->slider == (int)slider.setting)
	{
		p.a.x += (diffx / 10.0) / 2.0;
		mlx_mouse_get_pos(vars->win, &vars->clicked_co.x, &vars->clicked_co.y);
		new = (((vars->clicked_co.x) - p.a.x) / diffx) * slider.max;
		if ((vars->clicked_co.x > p.a.x + 5 || vars->clicked_co.x < p.a.x - 5))
		{
			if (vars->clicked_co.x > p.b.x)
				*(double *)slider.setting = slider.max;
			else if (vars->clicked_co.x < p.b.x - diffx)
				*(double *)slider.setting = slider.min;
			else if (new && *(double *)slider.setting + new <= slider.max
				&& *(double *)slider.setting + new >= slider.min)
				*(double *)slider.setting += new;
		}
	}
	else if (vars->clicking)
		if (vars->clicked_co.x >= p.a.x
			&& vars->clicked_co.x <= p.a.x + diffx / 10)
			if (vars->clicked_co.y >= p.a.y && vars->clicked_co.y <= p.b.y)
				vars->slider = (int)slider.setting;
}

void	slider(t_vars *vars, t_coords p, t_slider slider)
{
	int		dy;
	int		dx;
	double	diffx;

	diffx = (p.b.x - p.a.x);
	dy = p.a.y + ((p.b.y - p.a.y) / 4);
	while (dy < p.b.y - ((p.b.y - p.a.y) / 4))
	{
		dx = p.a.x;
		while (++dx < p.b.x)
			pixel_put(vars->img, dx, dy, to_rgb(p.a.c, 100));
		dy++;
	}
	dy = p.a.y;
	p.a.x += (int)round(((*(double *)slider.setting - slider.min)
				/ slider.max) * diffx - ((diffx / 10.0) / 2.0));
	while (dy < p.b.y)
	{
		dx = p.a.x;
		while (++dx < p.a.x + diffx / 10)
			pixel_put(vars->img, dx, dy, to_rgb(p.a.c, 200));
		dy++;
	}
	slider_test(vars, slider, p, diffx);
}
