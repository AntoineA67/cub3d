/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:22:08 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/14 14:31:39 by arangoni         ###   ########.fr       */
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
	int				n;
	double			prob;
	struct timeval	time;

	i = 0;
	//(int)(gettime(vars->n1) % 100)
	// i = -1;
	n = -1;
	prob = .0001;
	if (vars->usable_cells < 30)
	{
		vars->max_n_enemies = 0;
		return ;
	}
	while (vars->max_n_enemies < vars->usable_cells / 20 + 1)
	{
		gettimeofday(&time, NULL);
		printf("GEN ENEMY: %d %.2f %d %.2f\n", vars->max_n_enemies, prob, (int)(time.tv_usec) % 100, prob * 100);
		if (vars->parse_seen[i] == 1
			&& abs((int)vars->player.pos.x - i % vars->size.x) > 2 && abs((int)vars->player.pos.y - i % vars->size.y) > 2
			&& (int)(time.tv_usec) % 100 < (int)(prob * 100))
		{
			vars->enemies[++vars->max_n_enemies - 1].lives = 3;
			vars->enemies[vars->max_n_enemies - 1].last_attack = -1000;
			vars->enemies[vars->max_n_enemies - 1].pos.x = i % vars->size.x + .5;
			vars->enemies[vars->max_n_enemies - 1].pos.y = i / vars->size.x + .5;
			ft_memcpy(&vars->enemies[vars->max_n_enemies - 1].last_player_pos,
				&vars->enemies[vars->max_n_enemies - 1].pos, sizeof(t_vector2));
			printf("Enemy: %.2f %.2f\n", vars->enemies[vars->max_n_enemies - 1].pos.x,
				vars->enemies[vars->max_n_enemies - 1].pos.y);
			prob = 0.0;
		}
		if (vars->parse_seen[i] == 1)
			prob += 1.0 / vars->usable_cells;
		i = (i + 1) % vars->size.z;
	}

	// while (++i < vars->size.z && vars->max_n_enemies < vars->usable_cells / 20 + 1)
	// {
	// 	if (vars->parse_seen[i] == 1 && ++n % (int)(vars->usable_cells / 10) == 0)
	// 	{
	// 		vars->enemies[++vars->max_n_enemies - 1].lives = 3;
	// 		vars->enemies[vars->max_n_enemies - 1].last_attack = -1000;
	// 		vars->enemies[vars->max_n_enemies - 1].pos.x = i % vars->size.x + .5;
	// 		vars->enemies[vars->max_n_enemies - 1].pos.y = i / vars->size.x + .5;
	// 		ft_memcpy(&vars->enemies[vars->max_n_enemies - 1].last_player_pos,
	// 			&vars->enemies[vars->max_n_enemies - 1].pos, sizeof(t_vector2));
	// 		printf("Enemy: %.2f %.2f\n", vars->enemies[vars->max_n_enemies - 1].pos.x,
	// 			vars->enemies[vars->max_n_enemies - 1].pos.y);
	// 	} 
	// }
	vars->n_enemies = vars->max_n_enemies;
}