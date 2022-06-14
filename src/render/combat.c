/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:24:07 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/13 15:54:51 by qroussea         ###   ########lyon.fr   */
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

void	draw_bullets(t_vars *v, int i)
{
	double	angle;
	double	distbull;
	int		x;

	x = 0;
	if (v->bullets[i].pos.x > 0.0)
	{
		angle = atan2((v->player.pos.y - v->bullets[i].pos.y),
				(v->player.pos.x - v->bullets[i].pos.x));
		if (angle < 0)
			angle = M_PI * 2 + angle;
		angle = fmod(angle + M_PI, M_PI * 2);
		distbull = dist(v->player.pos.x, v->player.pos.y,
				v->bullets[i].pos.x, v->bullets[i].pos.y);
		if (angle > v->start && angle < v->end)
			x = v->win_size.x - (((v->end - angle) * v->win_size.x) / M_PI_2);
		else if ((angle + (M_PI * 2.0)) > v->start
			&& (angle + (M_PI * 2.0)) < v->end)
			x = v->win_size.x - (((v->end - (angle + (M_PI * 2.0)))
						* v->win_size.x) / M_PI_2);
		if (x < v->win_size.x && x > 0 && v->rays[x].dist > distbull)
			draw_square_texture_center(v, gen_coord(x, v->win_size.y / 2,
					(1 / distbull) * (v->win_size.y / 2) * .2, gen_color(100,
						100, 100, 0)), get_texture(v, "bullet", 0), distbull);
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

void	process_bullet(t_vars *vars, int i)
{
	t_vector2	newp;
	t_bullets	*act;

	act = vars->bullets + i;
	if (act->pos.x > 0)
	{
		newp.x = act->pos.x + act->delta.x * .5 * vars->delta_time_render * 25.;
		newp.y = act->pos.y + act->delta.y * .5 * vars->delta_time_render * 25.;
		if (((int)newp.y >= 0 && (int)newp.x < vars->size.x
				&& (int)newp.y < vars->size.y) && vars->map[(int)newp.x
				+ (int)act->pos.y * vars->size.x] != 'C'
			&& vars->map[(int)newp.x + (int)act->pos.y * vars->size.x] != '1')
		{
			act->pos.x = newp.x;
			if (vars->map[(int)act->pos.x + (int)newp.y * vars->size.x] != 'C'
				&& vars->map[(int)act->pos.x + (int)newp.y * vars->size.x] != 49
				&& !check_enemy_nearby(vars, &act->pos))
				act->pos.y = newp.y;
			else
				act->pos.x = -1;
		}
		else
			act->pos.x = -1;
	}
	draw_bullets(vars, i);
}

void	process_bullets(t_vars *vars)
{
	int			i;

	i = -1;
	while (++i < MAX_BULLETS)
		process_bullet(vars, i);
}

void	gen_bullet(t_vars *vars)
{
	int		i;
	time_t	cooldown;

	cooldown = gettime(vars->n1);
	if (cooldown - vars->bullet_cooldown < 300 || !vars->clicking)
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
