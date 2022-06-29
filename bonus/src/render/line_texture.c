/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:36:27 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/29 13:42:50 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	line_texture_draw(t_vars *vars, t_ltextcalc *calc)
{
	while (++calc->i < calc->draw_end)
	{
		*(unsigned int *)(vars->img->addr + (calc->i * vars->img->line_length
					+ calc->screen_x * vars->img->bits_per_pixel))
			= *(unsigned int *)(calc->img->addr + (calc->img_x + (int)calc->y
					* calc->img->line_length));
		calc->y += calc->step;
	}
}

void	line_texture_calc(t_vars *vars, t_ltextcalc	*calc)
{
	if (calc->wall_height < 2)
		calc->wall_height = 0;
	calc->y = 0.0;
	calc->step = (calc->img->size.y + .0) / (2 * calc->wall_height);
	calc->i = vars->win_size.y / 2 - calc->wall_height - vars->player.rot.y;
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
		- vars->player.rot.y;
	if (calc->draw_end > vars->win_size.y)
		calc->draw_end = vars->win_size.y;
	line_texture_draw(vars, calc);
}

void	line_texture(t_vars *vars, int x, char *t)
{
	t_ltextcalc	calc;

	calc.img = get_animtexture(vars, t, 0);
	if (vars->rays[x].rx < 0 || vars->rays[x].ry < 0 || vars->rays[x].rx
		> vars->size.x || vars->rays[x].ry > vars->size.y)
		return ;
	if (t[0] == 'n')
		calc.img_x = (vars->rays[x].rx - (int)vars->rays[x].rx)
			* (calc.img->size.x + .0);
	else if (t[0] == 's')
		calc.img_x = (1.0 - (vars->rays[x].rx
					- (int)vars->rays[x].rx)) * (calc.img->size.x + .0);
	else if (t[0] == 'e')
		calc.img_x = (vars->rays[x].ry - (int)vars->rays[x].ry)
			* (calc.img->size.x + .0);
	else
		calc.img_x = (1.0 - (vars->rays[x].ry - (int)vars->rays[x].ry))
			* (calc.img->size.x + .0);
	calc.wall_height = vars->win_size.y / 2 / vars->rays[x].dist * .90;
	calc.screen_x = x;
	line_texture_calc(vars, &calc);
}
