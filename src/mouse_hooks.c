/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:50:25 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/04 14:50:37 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	mouse_hook(int keycode, int x, int y, t_vars *vars)
{
	printf("%d %d\n", x, y);
	// printf("%d\n", keycode);
	if (keycode == 1)
	{
		// printf("%d|%d\n", x, y);
		vars->clicked = 1;
		vars->clicked_co.x = x;
		vars->clicked_co.y = y;
	}
	return (0);
}
