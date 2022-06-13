/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:50:25 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/11 13:09:30 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_hook_up(int keycode, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (keycode == 1)
	{
		vars->clicking = 0;
		vars->slider = 0;
	}
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_vars *vars)
{
	if (keycode == 1)
	{
		vars->clicked = 1;
		vars->clicking = 1;
		vars->clicked_co.x = x;
		vars->clicked_co.y = y;
	}
	else if (keycode == 4)
		vars->scroll++;
	else if (keycode == 5 && vars->scroll > 0)
		vars->scroll--;
	return (0);
}
