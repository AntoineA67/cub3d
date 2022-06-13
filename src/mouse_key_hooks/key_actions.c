/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:17:58 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/11 13:25:13 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	change_case(t_vars	*vars, double newposX, double newposY, t_vector2 *start)
{
	long	pos;
	long	posplayer;

	pos = (int)newposX + (int)newposY * vars->size.x;
	posplayer = (int)start->x + (int)start->y * vars->size.x;
	if (vars->map[pos - 1] == 'C')
		vars->map[pos - 1] = 'O';
	else if (vars->map[pos + 1] == 'C')
		vars->map[pos + 1] = 'O';
	else if (vars->map[pos + vars->size.x] == 'C')
		vars->map[pos + vars->size.x] = 'O';
	else if (vars->map[pos - vars->size.x] == 'C')
		vars->map[pos - vars->size.x] = 'O';
	// else if (vars->map[pos] != 'O')
	// {
	// 	if (vars->map[posplayer - 1] == 'O')
	// 		vars->map[posplayer - 1] = 'C';
	// 	else if (vars->map[posplayer + 1] == 'O')
	// 		vars->map[posplayer + 1] = 'C';
	// 	else if (vars->map[posplayer + vars->size.x] == 'O')
	// 		vars->map[posplayer + vars->size.x] = 'C';
	// 	else if (vars->map[posplayer - vars->size.x] == 'O')
	// 		vars->map[posplayer - vars->size.x] = 'C';
	// }
	return (0);
}

void	move_player(t_vars *vars, int dir_x, int dir_y)
{
	double	newposx;
	double	newposy;
	int		size;

	size = vars->min_map_mult;
	if (dir_x)
	{
		newposx = vars->player.pos.x + dir_x * cos(vars->player.rot.x) * (.1 + .05 * vars->player.run) * vars->delta_time * 20.0;
		newposy = vars->player.pos.y + dir_x * sin(vars->player.rot.x) * (.1 + .05 * vars->player.run) * vars->delta_time * 20.0;
	}
	else
	{
		newposx = vars->player.pos.x + dir_y * cos(vars->player.rot.x - M_PI_2) * (.05 + .02 * vars->player.run) * vars->delta_time * 20.0;
		newposy = vars->player.pos.y + dir_y * sin(vars->player.rot.x - M_PI_2) * (.05 + .02 * vars->player.run) * vars->delta_time * 20.0;	
	}
	if (vars->map[(int)newposx + (int)vars->player.pos.y * vars->size.x] == '1')
		newposx = vars->player.pos.x;
	if (vars->map[(int)vars->player.pos.x + (int)newposy * vars->size.x] == '1')
		newposy = vars->player.pos.y;
	if (vars->map[(int)newposx + (int)newposy * vars->size.x] != 'C')
	{
		if ((int)newposx + (int)newposy * vars->size.x != (int)vars->player.pos.x + (int)vars->player.pos.y * vars->size.x)
				change_case(vars, newposx, newposy, &vars->player.pos);
		vars->player.pos.x = newposx;
		vars->player.pos.y = newposy;
	}
}

void	rotate_player_x(t_vars *vars, int dir)
{
	vars->player.rot.x += dir * 0.002 * vars->settings.x_ratio_mouse_speed;
	if (vars->player.rot.x < 0.0)
		vars->player.rot.x += 2.0 * M_PI;
	else if (vars->player.rot.x > 2.0 * M_PI)
		vars->player.rot.x -= 2.0 * M_PI;
	vars->player.delta.x = cos(vars->player.rot.x);
	vars->player.delta.y = sin(vars->player.rot.x);
}

void	jump(t_vars *vars)
{
	if (vars->jump > 0 && gettime(vars->n1) - vars->jump < 1000)
		return ;
	vars->jump = gettime(vars->n1);
}