/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:22:08 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/13 15:15:57 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_bullets(t_vars *vars)
{
	int	i;

	vars->bullet_cooldown = -1;
	i = -1;
	while (++i < MAX_BULLETS)
	{
		vars->bullets[i].pos.x = -1;
	}
}

void	init_enemies(t_vars *vars)
{
	int				i;
	double			prob;
	struct timeval	time;

	i = 0;
	prob = .0001;
	while (vars->max_n_enemies < vars->usable_cells / 20 + 1)
	{
		gettimeofday(&time, NULL);
		if (vars->parse_seen[i] == 1
			&& abs((int)vars->player.pos.x - i % vars->size.x) > 2
			&& abs((int)vars->player.pos.y - i % vars->size.y) > 2
			&& (int)(time.tv_usec) % 100 < (int)(prob * 100))
		{
			vars->enemies[++vars->max_n_enemies - 1].lives = 3;
			vars->enemies[vars->max_n_enemies - 1].last_attack = -1000;
			vars->enemies[vars->max_n_enemies - 1].pos.x = i % vars->size.x + .5;
			vars->enemies[vars->max_n_enemies - 1].pos.y = i / vars->size.x + .5;
			ft_memcpy(&vars->enemies[vars->max_n_enemies - 1].last_player_pos,
				&vars->enemies[vars->max_n_enemies - 1].pos, sizeof(t_vector2));
			prob = 0.0;
		}
		if (vars->parse_seen[i] == 1)
			prob += 1.0 / vars->usable_cells;
		i = (i + 1) % vars->size.z;
	}
	vars->n_enemies = vars->max_n_enemies;
}