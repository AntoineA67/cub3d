/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:25:33 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/11 13:39:32 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	try_attack(t_vars *vars, t_enemy *enemy)
{
	time_t	attack_ts;

	attack_ts = gettime(vars->n1);
	if (attack_ts - enemy->last_attack < 1000)
		return (0);
	enemy->last_attack = attack_ts;
	vars->player.lives--;
	return (1);
}

void	process_enemies(t_vars *vars)
{
	int			i;
	double		angle;
	double		dist_enemy;
	t_vector2	new_pos;
	t_ray		ray;
	time_t		ts;

	ts = gettime(vars->n1);
	if (ts < 2000)
		return ;
	i = -1;
	while (++i < vars->max_n_enemies)
	{
		if (vars->enemies[i].lives > 0 && ts - vars->enemies[i].last_attack > 1000)
		{
			angle = atan2((vars->enemies[i].pos.y - vars->player.pos.y), (vars->enemies[i].pos.x - vars->player.pos.x));
			if (angle < 0)
				angle = M_PI * 2 + angle;
			angle =  angle + M_PI;
			angle = fmod(angle, M_PI * 2);
			// printf("player%d:%f|%f|%f\\%f\n",i,vars->start,angle,vars->end, angle + (M_PI * 2.0));
			dist_enemy = dist(vars->enemies[i].pos.x, vars->enemies[i].pos.y, vars->player.pos.x, vars->player.pos.y);
			//if (dist_enemy < .8 && try_attack(vars, &vars->enemies[i]))
				//return ;
			ray.ra2 = angle;
			ray.start_pos.x = vars->enemies[i].pos.x;
			ray.start_pos.y = vars->enemies[i].pos.y;
			calc_ray(vars, &ray);
			if (dist_enemy < ray.dist)
			{
				ft_memcpy(&vars->enemies[i].last_player_pos, &vars->player.pos, sizeof(t_vector2));
				new_pos.x = vars->enemies[i].pos.x + ((.08 - .16 * (vars->player.pos.x < vars->enemies[i].pos.x)) * vars->delta_time * 20.0 * (fabs(vars->enemies[i].pos.x - vars->player.pos.x) > .5));
				new_pos.y = vars->enemies[i].pos.y + ((.08 - .16 * (vars->player.pos.y < vars->enemies[i].pos.y)) * vars->delta_time * 20.0 * (fabs(vars->enemies[i].pos.y - vars->player.pos.y) > .5));
				// printf("%.2f %.2f	%.2f %.2f\n", new_pos.x, new_pos.y, fabs(vars->enemies[i].pos.x - vars->player.pos.x), fabs(vars->enemies[i].pos.y - vars->player.pos.y));
				change_case(vars, new_pos.x, new_pos.y, &vars->enemies[i].pos);
				vars->enemies[i].pos.x = new_pos.x;
				vars->enemies[i].pos.y = new_pos.y;
			}
			else
			{
				new_pos.x = vars->enemies[i].pos.x + ((.08 - .16 * (vars->enemies[i].last_player_pos.x < vars->enemies[i].pos.x)) * vars->delta_time * 20.0 * (fabs(vars->enemies[i].pos.x - vars->enemies[i].last_player_pos.x) > .5));
				new_pos.y = vars->enemies[i].pos.y + ((.08 - .16 * (vars->enemies[i].last_player_pos.y < vars->enemies[i].pos.y)) * vars->delta_time * 20.0 * (fabs(vars->enemies[i].pos.y - vars->enemies[i].last_player_pos.y) > .5));
				// printf("%.2f %.2f	%.2f %.2f\n", new_pos.x, new_pos.y, fabs(vars->enemies[i].pos.x - vars->player.pos.x), fabs(vars->enemies[i].pos.y - vars->player.pos.y));
				change_case(vars, new_pos.x, new_pos.y, &vars->enemies[i].pos);
				vars->enemies[i].pos.x = new_pos.x;
				vars->enemies[i].pos.y = new_pos.y;
			}
		}
	}
}

void	draw_enemies(t_vars *vars)
{
	int		i;
	double	angle;
	double	dist_enemy;
	double	dangle;
	int		screen_x;
	double	sprite_size;

	i = -1;
	while (++i < vars->max_n_enemies)
	{
		if (vars->enemies[i].lives > 0)
		{
			angle = atan2((vars->player.pos.y - vars->enemies[i].pos.y), (vars->player.pos.x - vars->enemies[i].pos.x));
			if (angle < 0)
				angle = M_PI * 2 + angle;
			angle =  angle + M_PI;
			angle = fmod(angle, M_PI * 2);
			// printf("player%d:%f|%f|%f\\%f\n",i,vars->start,angle,vars->end, angle + (M_PI * 2.0));
			dist_enemy = dist(vars->player.pos.x, vars->player.pos.y, vars->enemies[i].pos.x, vars->enemies[i].pos.y);
			sprite_size = (1.0 / dist_enemy) * (vars->win_size.y / 2.0);
			if (angle > vars->start && angle < vars->end)
				dangle = vars->end - angle;
			else
				dangle = vars->end - (angle + (M_PI * 2.0));
			screen_x = vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2);
			//if ((screen_x - sprite_size / 2 < vars->win_size.x || screen_x + sprite_size / 2 > 0) && vars->rays[screen_x].dist > dist_enemy)
			if (screen_x >= 0 && screen_x < vars->win_size.x && vars->rays[screen_x].dist > dist_enemy)
			{
				draw_square_texture_center(vars, gen_coord(screen_x, vars->win_size.y / 2, sprite_size, gen_color(100,100,100,0)), get_texture(vars, "aaa", 0), dist_enemy);
			}
		}
	}
}
