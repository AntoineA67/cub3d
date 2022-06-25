/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:17:58 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/25 15:46:59 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_vars *vars, int dir_x, int dir_y)
{
	double	newposx;
	double	newposy;

	if (dir_x)
	{
		newposx = vars->player.pos.x + dir_x
			* cos(vars->player.rot.x) * (.1 + .05);
		newposy = vars->player.pos.y + dir_x
			* sin(vars->player.rot.x) * (.1 + .05);
	}
	else
	{
		newposx = vars->player.pos.x + dir_y
			* cos(vars->player.rot.x - M_PI_2) * (.05 + .02);
		newposy = vars->player.pos.y + dir_y
			* sin(vars->player.rot.x - M_PI_2) * (.05 + .02);
	}
	vars->player.pos.x = newposx;
	vars->player.pos.y = newposy;
}

void	rotate_player_x(t_vars *vars, int dir)
{
	vars->player.rot.x += dir * 0.002;
	if (vars->player.rot.x < 0.0)
		vars->player.rot.x += 2.0 * M_PI;
	else if (vars->player.rot.x > 2.0 * M_PI)
		vars->player.rot.x -= 2.0 * M_PI;
	vars->player.delta.x = cos(vars->player.rot.x);
	vars->player.delta.y = sin(vars->player.rot.x);
}
