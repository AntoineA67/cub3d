/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:50:25 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/29 14:27:34 by qroussea         ###   ########lyon.fr   */
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
	return (0);
}
