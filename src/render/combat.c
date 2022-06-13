/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:24:07 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/11 12:37:57 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_2d_enemies(t_vars *vars, int size)
{
	int	i;

	i = -1;
	while (++i < vars->max_n_enemies)
	{
		if (vars->enemies[i].lives > 0)
		{
			draw_square_center(vars,
				gen_coord(vars->enemies[i].pos.x * size + size,
					vars->enemies[i].pos.y * size + size, size / 2,
					gen_color(0, 0, 255, 0)));
		}
	}
}

void	draw_bullets(t_vars *v)
{
	int		i;
	double	angle;
	double	dist_bullet;
	int		screen_x;

	i = -1;
	while (++i < MAX_CLIENT)
	{
		if (v->bullets[i].pos.x > 0.0)
		{
			angle = atan2((v->player.pos.y - v->bullets[i].pos.y),
					(v->player.pos.x - v->bullets[i].pos.x));
			if (angle < 0)
				angle = M_PI * 2 + angle;
			angle = fmod(angle + M_PI, M_PI * 2);
			dist_bullet = dist(v->player.pos.x, v->player.pos.y, v->bullets[i].pos.x, v->bullets[i].pos.y);
			if (angle > v->start && angle < v->end)
				screen_x = v->win_size.x - (((v->end - angle) * v->win_size.x) / M_PI_2);
			else if (( angle + (M_PI * 2.0)) > v->start && (angle + (M_PI * 2.0)) < v->end)
				screen_x = v->win_size.x - (((v->end - (angle + (M_PI * 2.0))) * v->win_size.x) / M_PI_2);
			if (screen_x < v->win_size.x && screen_x > 0 && v->rays[screen_x].dist > dist_bullet)	
				draw_square_texture_center(v, gen_coord(screen_x, v->win_size.y
				/ 2, (1 / dist_bullet) * (v->win_size.y / 2) * .2, gen_color(100,100,100,0)), get_texture(v, "bullet", 0), dist_bullet);
		}
	}
}

int	check_enemy_nearby(t_vars *vars, t_vector2 *bullet_pos)
{
	int		i;
	double	hitbox;

	i = -1;
	hitbox = .3;
	while (++i < vars->max_n_enemies)
	{
		if (vars->enemies[i].lives > 0)
		{
			if (bullet_pos->x > vars->enemies[i].pos.x - hitbox
				&& bullet_pos->x < vars->enemies[i].pos.x + hitbox
				&& bullet_pos->y > vars->enemies[i].pos.y - hitbox
				&& bullet_pos->y < vars->enemies[i].pos.y + hitbox)
			{
				vars->enemies[i].lives--;
				return (1);
			}
		}
	}
	return (0);
}

void	process_bullets(t_vars *vars)
{
	int			i;
	t_vector2	new_pos;
	t_bullets	*act;

	i = -1;
	while (++i < MAX_BULLETS)
	{
		act = vars->bullets + i;
		if (act->pos.x > 0)
		{
			new_pos.x = act->pos.x + act->delta.x * .5 * vars->delta_time_render * 25.0;
			new_pos.y = act->pos.y + act->delta.y * .5 * vars->delta_time_render * 25.0;
			if (((int)new_pos.y >= 0 && (int)new_pos.x < vars->size.x
			 && (int)new_pos.y < vars->size.y) && vars->map[(int)new_pos.x + (int)act->pos.y * vars->size.x] != 'C'
				&& vars->map[(int)new_pos.x + (int)act->pos.y * vars->size.x] != '1')
				{
					act->pos.x = new_pos.x;
					if (vars->map[(int)act->pos.x + (int)new_pos.y * vars->size.x] != 'C'
						&& vars->map[(int)act->pos.x + (int)new_pos.y * vars->size.x] != '1'
						&& !check_enemy_nearby(vars, &act->pos))
						act->pos.y = new_pos.y;
					else
						act->pos.x = -1;
				}
			else
				act->pos.x = -1;
		}
	}
}

void	gen_bullet(t_vars *vars)
{
	int		i;
	time_t	cooldown;

	cooldown = gettime(vars->n1);
	if (cooldown - vars->bullet_cooldown < 300
		|| vars->mult_fd || !vars->clicking)
		return ;
	vars->bullet_cooldown = cooldown;
	i = -1;
	while (++i < MAX_BULLETS)
		if (vars->bullets[i].pos.x < 0)
			break ;
	if (i == MAX_BULLETS)
		return ;
	vars->bullets[i].pos.x = vars->player.pos.x;
	vars->bullets[i].pos.y = vars->player.pos.y;
	vars->bullets[i].delta.x = cos(vars->player.rot.x);
	vars->bullets[i].delta.y = sin(vars->player.rot.x);
}
