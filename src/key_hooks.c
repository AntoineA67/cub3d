/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:58:30 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/07 11:59:38 by arangoni         ###   ########.fr       */
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

	pos = (int)newposX + (int)newposY * vars->size.x;
	posplayer = (int)vars->player.pos.x + (int)vars->player.pos.y * vars->size.x;
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

static void	move_player(t_vars *vars, int dir_x, int dir_y)
{
	double	newposX;
	double	newposY;
	int		size;

	size = vars->min_map_mult;
	if (dir_x)
	{
		newposX = vars->player.pos.x + dir_x * cos(vars->player.rot.x) * 0.1;
		newposY = vars->player.pos.y + dir_x * sin(vars->player.rot.x) * 0.1;
	}
	else
	{
		newposX = vars->player.pos.x + dir_y * cos(vars->player.rot.x - M_PI_2) * 0.05;
		newposY = vars->player.pos.y + dir_y * sin(vars->player.rot.x - M_PI_2) * 0.05;	
	}
	// printf("%.2f	%.2f\n", newposX, newposY);
	if (vars->map[(int)newposX + (int)newposY * vars->size.x] != '1')
	{
		if (vars->map[(int)newposX + (int)newposY * vars->size.x] != 'C')
		{
			if ((int)newposX + (int)newposY * vars->size.x != (int)vars->player.pos.x + (int)vars->player.pos.y * vars->size.x)
					change_case(vars, newposX, newposY);
			vars->player.pos.x = newposX;
			vars->player.pos.y = newposY;
		}
	}
	// printf("AAA: %.2f %.2f - %d %d - %c %d\n", newposX, newposY,
	 //	(int)newposX / 64, (int)newposY / 64, vars->map[(int)((newposX / 64) + (newposY / 64) * vars->size.x)], (int)(((int)newposX / 64) + ((int)newposY / 64) * vars->size.x));
}

void	rotate_player_x(t_vars *vars, int dir)
{
	vars->player.rot.x += dir / 100.0;
	// printf("%.2f\n", vars->player.rot.x);
	if (vars->player.rot.x < 0.0)
		vars->player.rot.x += 2.0 * M_PI;
	else if (vars->player.rot.x > 2.0 * M_PI)
		vars->player.rot.x -= 2.0 * M_PI;
	vars->player.delta.x = cos(vars->player.rot.x);
	vars->player.delta.y = sin(vars->player.rot.x);
}

// int	key_hook(int keycode, t_vars *vars) //WSL2 VERSION
// {
// 	dprintf(1, "%d\n", keycode);
// 	if (keycode == 65307)
// 	{
// 		if (vars->ui == 1)
// 			esc(vars, 0);
// 		else
// 		{
// 				ft_int_memset(vars->img->addr, 0x000000,
// 		vars->img->line_length * vars->win_size.y / 4);
// 			vars->ui = 1;
// 		}
// 	}
// 	if (vars->ui)
// 		return (0);
// 	else if (keycode == 113)
// 		rotate_player(vars, -1);
// 	else if (keycode == 115)
// 		move_player(vars, -1);
// 	else if (keycode == 100)
// 		rotate_player(vars, 1);
// 	else if (keycode == 122)
// 		move_player(vars, 1);
// 	else if (keycode == 44 && !vars->mult_fd && serv_connect(vars))
// 		esc(vars, 1);
// 	//project(vars);
// 	printf("Pos: %.2f %.2f - %3d %3d	Rot: %.2f Delta: %.2f %.2f\n",
// 			vars->player.pos.x, vars->player.pos.y, (int)vars->player.pos.x / 64, (int)vars->player.pos.y / 64,
// 			 vars->player.rot.x, vars->player.delta.x, vars->player.delta.y);
// 	return (0);
// }

int	key_hook_down(int keycode, t_vars *vars)
{
	if (keycode < 200)
		vars->keyboard[keycode] = 1;
	return (0);
}

int	key_hook_up(int keycode, t_vars *vars)
{
	if (keycode < 200)
		vars->keyboard[keycode] = 0;
	return (0);
}

int	check_inputs(t_vars *vars)
{
	if (vars->keyboard[53])
	{
		if (vars->ui == 1)
			esc(vars, 0);
		else
		{
			mlx_mouse_show();
			ft_int_memset(vars->img->addr, 0x000000,
				vars->img->line_length * vars->win_size.y / 4);
			vars->ui = 1;
		}
	}
	if (vars->ui)
		return (0);
	if (vars->keyboard[0])
		move_player(vars, 0, 1);
	if (vars->keyboard[123])
		rotate_player_x(vars, -10);
	if (vars->keyboard[1])
		move_player(vars, -1, 0);
	if (vars->keyboard[2])
		move_player(vars, 0, -1);
	if (vars->keyboard[124])
		rotate_player_x(vars, 10);
	if (vars->keyboard[13])
		move_player(vars, 1, 0);
	if (vars->keyboard[46] && !vars->mult_fd && serv_connect(vars))
 		esc(vars, 1);
	//project(vars);
	// printf("Pos: %.2f %.2f - %3d %3d	Rot: %.2f Delta: %.2f %.2f\n",
			// vars->player.pos.x, vars->player.pos.y, (int)vars->player.pos.x / 64, (int)vars->player.pos.y / 64,
			//  vars->player.rot.x, vars->player.delta.x, vars->player.delta.y);
	return (0);
}
