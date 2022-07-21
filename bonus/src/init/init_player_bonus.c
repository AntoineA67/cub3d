/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:10:30 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/25 14:23:07 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_player(t_vars *vars)
{
	char	*player_in_map;

	vars->player.lives = 3;
	vars->player.rot.x = -vars->start_rot;
	vars->player.rot.y = 0;
	vars->player.delta.x = 0;
	vars->player.delta.y = 0;
	player_in_map = ft_strchr(vars->map, 'P');
	vars->map[player_in_map - vars->map] = '0';
	vars->player.pos.x = (player_in_map - vars->map) % vars->size.x + .5;
	vars->player.pos.y = (player_in_map - vars->map) / vars->size.x + .5;
	return (0);
}
