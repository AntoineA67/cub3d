/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:50:25 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/22 21:48:09 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	mouse_hook(int keycode, int x, int y, t_vars *vars)
{
	float	rotation;

	(void)x;
	(void)y;
	rotation = .06;
	if (keycode == 4)
		vars->zoom += 1;
	else if (keycode == 5 && vars->zoom > 1)
		vars->zoom -= 1;
	project(vars);
	return (0);
}
