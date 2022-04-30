/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:58:30 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/30 13:19:25 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// static void	key_rotate(t_vars *vars, int keycode)
// {
// 	if (keycode == 126)
// 		vars->rotation.x = (vars->rotation.x + 5 * vars->proj_type) % 360;
// 	else if (keycode == 125)
// 		vars->rotation.x = (vars->rotation.x - 5 * vars->proj_type) % 360;
// 	else if (keycode == 123)
// 		vars->rotation.z = (vars->rotation.z + 5 * vars->proj_type) % 360;
// 	else if (keycode == 124)
// 		vars->rotation.z = (vars->rotation.z - 5 * vars->proj_type) % 360;
// }

// static void	key_translate(t_vars *vars, int keycode)
// {
// 	if (keycode == 0)
// 		vars->translate.x += 20;
// 	if (keycode == 1)
// 		vars->translate.y -= 20;
// 	if (keycode == 2)
// 		vars->translate.x -= 20;
// 	if (keycode == 13)
// 		vars->translate.y += 20;
// }

// static void	key_color(t_vars *vars)
// {
// 	if (vars->color.v)
// 	{
// 		vars->color.v = 0;
// 		vars->color.r = 255;
// 		vars->color.g = 255;
// 		vars->color.b = 255;
// 		return ;
// 	}
// 	vars->color.r = 255;
// 	vars->color.g = 0;
// 	vars->color.b = 0;
// 	vars->color.v = 1;
// }

// static void	switch_projection(t_vars *vars)
// {
// 	if (vars->proj_type == 18)
// 	{
// 		vars->proj_type = 1;
// 		coord(&vars->rotation, -55, 0, -45);
// 	}
// 	else
// 	{
// 		vars->proj_type = 18;
// 		coord(&vars->rotation, 0, 0, 0);
// 	}
// }

int	change_case(t_vars	*vars, double newposX, double newposY)
{
	long	pos;
	long	posplayer;

	pos = ((int)newposX/(int)vars->min_map_mult) + ((int)newposY/(int)vars->min_map_mult) * vars->size.x;
	posplayer = ((int)vars->player.pos.x/(int)vars->min_map_mult) + ((int)vars->player.pos.y/(int)vars->min_map_mult) * vars->size.x;
	if (vars->map[pos - 1] == 'C')
		vars->map[pos - 1] = 'O';
	else if (vars->map[pos + 1] == 'C')
		vars->map[pos + 1] = 'O';
	else if (vars->map[pos + vars->size.x] == 'C')
		vars->map[pos + vars->size.x] = 'O';
	else if (vars->map[pos - vars->size.x] == 'C')
		vars->map[pos - vars->size.x] = 'O';
	else if (vars->map[pos] != 'O')
	{
	if (vars->map[posplayer - 1] == 'O')
		vars->map[posplayer - 1] = 'C';
	else if (vars->map[posplayer + 1] == 'O')
		vars->map[posplayer + 1] = 'C';
	else if (vars->map[posplayer + vars->size.x] == 'O')
		vars->map[posplayer + vars->size.x] = 'C';
	else if (vars->map[posplayer - vars->size.x] == 'O')
		vars->map[posplayer - vars->size.x] = 'C';
	}
	return (0);
}

static void	move_player(t_vars *vars, int dir)
{
	double	newposX;
	double	newposY;
	int		size;

	size = vars->min_map_mult;
	newposX = vars->player.pos.x + dir * cos(vars->player.rot) * (size / 4);
	newposY = vars->player.pos.y + dir * sin(vars->player.rot) * (size / 4);
	if (vars->map[((int)newposX/size) + ((int)newposY/size) * vars->size.x] != '1')
	{
		if (vars->map[((int)newposX/size) + ((int)newposY/size) * vars->size.x] != 'C')
		{
			if (((int)newposX/size) + ((int)newposY/size) * vars->size.x != ((int)vars->player.pos.x/size) + ((int)vars->player.pos.y/size) * vars->size.x)
					change_case(vars, newposX, newposY);
			vars->player.pos.x = newposX;
			vars->player.pos.y = newposY;
		}
	}
	// printf("AAA: %.2f %.2f - %d %d - %c %d\n", newposX, newposY,
	 //	(int)newposX / 64, (int)newposY / 64, vars->map[(int)((newposX / 64) + (newposY / 64) * vars->size.x)], (int)(((int)newposX / 64) + ((int)newposY / 64) * vars->size.x));
}

static void	rotate_player(t_vars *vars, int dir)
{
	vars->player.rot += dir / 10.0;
	// printf("%.2f\n", vars->player.rot);
	if (vars->player.rot < 0.0)
		vars->player.rot += 2.0 * M_PI;
	else if (vars->player.rot > 2.0 * M_PI)
		vars->player.rot -= 2.0 * M_PI;
	vars->player.delta.x = cos(vars->player.rot) * 5.0;
	vars->player.delta.y = sin(vars->player.rot) * 5.0;
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 0)
		rotate_player(vars, -1);
	else if (keycode == 1) 
		move_player(vars, -1);
	else if (keycode == 2)
		rotate_player(vars, 1);
	else if (keycode == 13)
		move_player(vars, 1);
	else if (keycode == 53)
		esc(vars, 0);
	//project(vars);
	// printf("Pos: %.2f %.2f - %3d %3d	Rot: %.2f Delta: %.2f %.2f\n",
			// vars->player.pos.x, vars->player.pos.y, (int)vars->player.pos.x / 64, (int)vars->player.pos.y / 64,
			//  vars->player.rot, vars->player.delta.x, vars->player.delta.y);
	return (0);
}
