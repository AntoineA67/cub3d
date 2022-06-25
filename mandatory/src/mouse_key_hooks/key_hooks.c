/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:58:30 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/25 15:46:34 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_hook_down(int keycode, t_vars *vars)
{
	if (keycode < 300)
		vars->keyboard[keycode] = 1;
	return (0);
}

int	key_hook_up(int keycode, t_vars *vars)
{
	if (keycode < 300)
		vars->keyboard[keycode] = 0;
	return (0);
}

int	check_inputs2(t_vars *vars)
{
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
	return (0);
}

int	check_inputs(t_vars *vars)
{
	if (vars->keyboard[53])
		exit_err(vars, 0);
	if (vars->keyboard[35])
		exit_err(vars, 0);
	return (check_inputs2(vars));
}
