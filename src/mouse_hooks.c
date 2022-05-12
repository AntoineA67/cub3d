/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:50:25 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/12 12:52:06 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	mouse_hook_up(int keycode, int x, int y, t_vars *vars)
{
	//  printf("%d|%d|%d\n", keycode,x,y);
	//  printf("%f|%f\n", vars->settings.y_ratio_mouse_speed, vars->settings.fps_cap);
	if (keycode == 1)
	{
		vars->clicking = 0;
		vars->slider = 0;
	}
	 (void)x;
	 (void)y;
	// if (keycode < 300)
	// 	vars->keyboard[keycode] = 0;
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_vars *vars)
{
	// printf("%d %d\n", x, y);
	// printf("%d\n", keycode);
	if (keycode == 1)
	{
		// printf("%d|%d\n", x, y);
		vars->clicked = 1;
		vars->clicking = 1;
		vars->clicked_co.x = x;
		vars->clicked_co.y = y;
		if (!vars->mult_fd && vars->bullets[0].pos.x < 0 && !vars->ui)
			gen_bullet(vars);
	}
	return (0);
}
