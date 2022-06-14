/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:36:27 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/14 14:44:12 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	line_texture_draw(t_vars *vars, t_ltextcalc *calc)
{
	unsigned int	oui;
	unsigned int	*add;
	double			isize;

	isize = 1.0 / (calc->img->size.y + 1.0);
	while (++calc->i < calc->draw_end)
	{
		oui = add_shade(vars, *(unsigned int *)(calc->img->addr + (calc->img_x
						+ (int)calc->y * calc->img->line_length)),
				(int)(vars->rays[calc->screen_x].dist * 10.0), vars->ao
				* (calc->ao + (1 - sin((((calc->y + 1) * isize)) * M_PI))
					* vars->ao_scale));
		add = (unsigned int *)(vars->img->addr
				+ (calc->i * vars->img->line_length + calc->screen_x
					* vars->img->bits_per_pixel));
		for (size_t i = 0; i < pow(2., vars->settings.m); i++)
		{
			*(add + i) = oui;
		}
		calc->y += calc->step;
	}
}

void	line_texture_calc(t_vars *vars, t_ltextcalc	*calc)
{
	if (calc->wall_height < 2)
		calc->wall_height = 0;
	calc->y = 0.0;
	calc->step = (calc->img->size.y + .0) / (2 * calc->wall_height);
	calc->i = vars->win_size.y / 2 - calc->wall_height - vars->player.rot.y
		- (vars->jump_height / vars->rays[calc->screen_x].dist);
	if (calc->i < 0)
	{
		calc->y = calc->step * (-calc->i);
		calc->i = -1;
	}
	if (calc->img_x < 0)
		calc->img_x = 0;
	if (calc->y < 0.0)
		calc->y = 0.0;
	if (calc->img_x > calc->img->size.x)
		return ;
	calc->img_x *= 4;
	calc->draw_end = vars->win_size.y / 2 + calc->wall_height
		- vars->player.rot.y - (vars->jump_height
			/ vars->rays[calc->screen_x].dist);
	if (calc->draw_end > vars->win_size.y)
		calc->draw_end = vars->win_size.y;
	line_texture_draw(vars, calc);
}

void	line_texture(t_vars *vars, int x, int rot, double ao)
{
	t_ltextcalc	calc;

	if (rot == 0 || rot == 1)
	{
		if (rot == 0)
			calc.img = get_animtexture(vars, "no", 0.2);
		else
			calc.img = get_animtexture(vars, "so", 0.2);
		calc.img_x = (vars->rays[x].rx - (int)vars->rays[x].rx)
			* (calc.img->size.x + .0);
	}
	if (rot == 2 || rot == 3)
	{
		if (rot == 2)
			calc.img = get_animtexture(vars, "we", 0.2);
		else
			calc.img = get_animtexture(vars, "ea", 0.2);
		calc.img_x = (vars->rays[x].ry - (int)vars->rays[x].ry)
			* (calc.img->size.x + .0);
	}
	calc.wall_height = vars->win_size.y / 2 / vars->rays[x].dist * .90;
	calc.ao = ao * vars->ao_scale;
	calc.screen_x = x;
	line_texture_calc(vars, &calc);
}
