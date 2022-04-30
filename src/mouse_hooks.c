/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:50:25 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/30 15:32:42 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	mouse_hook(int keycode, int x, int y, t_vars *vars)
{
	printf("%d\n", keycode);
	if (keycode == 1)
	{
		printf("%d|%d\n", x, y);
		vars->clicked = 1;
		vars->clicked_co.x = x;
		vars->clicked_co.y = y;
	}
	return (0);
}
