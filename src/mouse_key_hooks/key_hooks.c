/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:58:30 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/13 15:34:37 by qroussea         ###   ########lyon.fr   */
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
	if (vars->keyboard[45])
	{
		vars->keyboard[45] = 0;
		vars->ao = !vars->ao;
	}
	if (vars->keyboard[9] && vars->ao_scale > .05)
		vars->ao_scale -= .05;
	if (vars->keyboard[11] && vars->ao_scale < .95)
		vars->ao_scale += .05;
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
		escap(vars);
	if (vars->ui)
		return (0);
	if (vars->keyboard[257])
	{
		vars->keyboard[257] = 0;
		vars->player.run = !vars->player.run;
	}
	if (vars->keyboard[48])
	{
		vars->keyboard[48] = 0;
		vars->settings.map_type++;
		if (vars->settings.map_type == 3)
			vars->settings.map_type = 0;
	}
	if (vars->keyboard[49])
		jump(vars);
	return (check_inputs2(vars));
}
