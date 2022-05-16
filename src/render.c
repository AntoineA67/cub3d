/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:54:13 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/16 15:22:01 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

double	dist(double ax, double ay, double bx, double by, double angle)
{
	(void)angle;
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	draw_easy_texture(t_vars *vars, t_coord p, t_data *img)
{
	int		dy;
	int		dx;
	int		square_size;
	double	ratio_x;
	double	ratio_y;
	double	img_x;
	double	img_y;

	if (!p.z)
		return ;
	square_size = p.z;
	img_y = 0;
	ratio_x = (img->size.x + .0) / (square_size + .0);
	ratio_y = (img->size.y + .0) / (square_size + .0);
	dy = p.y - p.z / 2;
	while (++dy < p.y + p.z / 2)
	{
		dx = p.x - p.z / 2;
		img_x = 0;
		while (++dx < p.x + p.z / 2 && img_x < img->size.x && img_y >= 0 && img_x >= 0 && img_y < img->size.y && is_in_window(vars, dx, dy))
		{
			//printf("img_x: %f	img_y: %f\n", img_x, img_y);
			//printf("%d\n", img->line_length);
			// if ((*(unsigned int *)(img->addr + ((int)((int)img_x * (img->bits_per_pixel / 8)) + (int)((int)img_y * img->line_length)))>>24) != 255)
			pixel_put(vars->img, dx, dy,
				*(unsigned int *)(img->addr + ((int)((int)img_x * (img->bits_per_pixel / 8)) + (int)((int)img_y * img->line_length))));
			// else
				// printf("aaa\n");
			img_x += ratio_x;
		}
		img_y += ratio_y;
	}
}

void	draw_square_texture_center(t_vars *vars, t_coord p, t_data *img, double dist_b_players)
{
	int		dy;
	int		dx;
	int		square_size;
	double	ratio_x;
	double	ratio_y;
	double	img_x;
	double	img_y;

	if (!p.z)
		return ;
	square_size = p.z;
	img_y = 0;
	(void)dist_b_players;
	ratio_x = (img->size.x + .0) / (square_size + .0);
	ratio_y = (img->size.y + .0) / (square_size + .0);
	dy = p.y - p.z / 2;
	// printf("img_x: %d	img_y: %d\nsquare_size: %d\nratio_x: %.2f	ratio_y: %.2f\n", img->size.x, img->size.y, square_size, ratio_x, ratio_y);
	// draw_square_center(vars, p);
	while (++dy < p.y + p.z / 2)
	{
		dx = p.x - p.z / 2;
		img_x = 0;
		while (++dx < p.x + p.z / 2 && img_x < img->size.x && img_y >= 0 && img_x >= 0 && img_y < img->size.y && is_in_window(vars, dx, dy - vars->player.rot.y - vars->jump_height / dist_b_players))
		{
			//printf("img_x: %f	img_y: %f\n", img_x, img_y);
			//printf("%d\n", img->line_length);
			// if ((*(unsigned int *)(img->addr + ((int)((int)img_x * (img->bits_per_pixel / 8)) + (int)((int)img_y * img->line_length)))>>24) != 255)
				pixel_put(vars->img, dx, dy - vars->player.rot.y - vars->jump_height / dist_b_players,
					*(unsigned int *)(img->addr + ((int)((int)img_x * (img->bits_per_pixel / 8)) + (int)((int)img_y * img->line_length))));
			// else
				// printf("aaa\n");
			img_x += ratio_x;
		}
		img_y += ratio_y;
	}
}

void	draw_enemies(t_vars *vars)
{
	int		i;
	double	angle;
	double	dist_enemy;
	double	dangle;
	int		screen_x;

	i = -1;
	while (++i < vars->n_enemies)
	{
		if (vars->enemies[i].lives > 0)
		{
			angle = atan2((vars->player.pos.y - vars->enemies[i].pos.y), (vars->player.pos.x - vars->enemies[i].pos.x));
			if (angle < 0)
				angle = M_PI * 2 + angle;
			angle =  angle + M_PI;
			angle = fmod(angle, M_PI * 2);
			// printf("player%d:%f|%f|%f\\%f\n",i,vars->start,angle,vars->end, angle + (M_PI * 2.0));
			dist_enemy = dist(vars->player.pos.x, vars->player.pos.y, vars->enemies[i].pos.x, vars->enemies[i].pos.y, angle);
			if (angle > vars->start && angle < vars->end)
			{
				dangle = vars->end - angle;
				screen_x = vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2);
				if (screen_x < vars->win_size.x && screen_x > 0 && vars->rays[screen_x].dist > dist_enemy)
				{
					draw_square_texture_center(vars, gen_coord(screen_x, vars->win_size.y / 2, (1 / dist_enemy) * (vars->win_size.y / 2), gen_color(100,100,100,0)), get_texture(vars, "aaa", 0), dist_enemy);
				}
				// draw_square_texture_center(vars, gen_coord(vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2), vars->win_size.y / 2, (1 / dist(vars->player.pos.x, vars->player.pos.y, vars->mult_positions[i].x, vars->mult_positions[i].y, angle)) * 200, gen_color(100,100,100,0)), get_animtexture(vars, "player", 0.2));
				// draw_square_center(vars, gen_coord(vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2), vars->win_size.y / 2, (1 / dist(vars->player.pos.x, vars->player.pos.y, vars->mult_positions[i].x, vars->mult_positions[i].y, angle)) *100 , gen_color(100,100,100,0)));
			}
			else if (( angle + (M_PI * 2.0)) > vars->start && (angle + (M_PI * 2.0)) < vars->end)
			{
				dangle = vars->end - (angle + (M_PI * 2.0));
				screen_x = vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2);
				if (screen_x < vars->win_size.x && screen_x > 0 && vars->rays[screen_x].dist > dist_enemy)
				{
					draw_square_texture_center(vars, gen_coord(screen_x, vars->win_size.y / 2, (1 / dist_enemy) * (vars->win_size.y / 2), gen_color(100,100,100,0)), get_texture(vars, "aaa", 0), dist_enemy);	
				}
				// draw_square_center(vars, gen_coord(vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2), vars->win_size.y / 2, (1 / dist(vars->player.pos.x, vars->player.pos.y, vars->mult_positions[i].x, vars->mult_positions[i].y, angle)) *100 , gen_color(100,100,100,0)));	
			}
		}
	}
}

void	draw_other_players(t_vars *vars)
{
	int		i;
	double	angle;
	double	dist_players;
	double	dangle;
	int		screen_x;

	i = -1;
	while (++i < vars->mult_n_players && i < MAX_CLIENT)
	{
		if (vars->mult_id != i)
		{
			if (vars->mult_positions[i].y > 0.0 && vars->mult_positions[i].x > 0.0)
			{
				angle = atan2((vars->player.pos.y - vars->mult_positions[i].y), (vars->player.pos.x - vars->mult_positions[i].x));
				if (angle < 0)
					angle = M_PI * 2 + angle;
				angle =  angle + M_PI;
				angle = fmod(angle, M_PI * 2);
				// printf("player%d:%f|%f|%f\\%f\n",i,vars->start,angle,vars->end, angle + (M_PI * 2.0));
				dist_players = dist(vars->player.pos.x, vars->player.pos.y, vars->mult_positions[i].x, vars->mult_positions[i].y, angle);
				if (angle > vars->start && angle < vars->end)
				{
					dangle = vars->end - angle;
					screen_x = vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2);
					if (screen_x < vars->win_size.x && screen_x > 0 && vars->rays[screen_x].dist > dist_players)
						draw_square_texture_center(vars, gen_coord(screen_x, vars->win_size.y / 2, (1 / dist_players) * (vars->win_size.y / 2), gen_color(100,100,100,0)), get_texture(vars, "oui", 0), dist_players);
					// draw_square_texture_center(vars, gen_coord(vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2), vars->win_size.y / 2, (1 / dist(vars->player.pos.x, vars->player.pos.y, vars->mult_positions[i].x, vars->mult_positions[i].y, angle)) * 200, gen_color(100,100,100,0)), get_animtexture(vars, "player", 0.2));
					// draw_square_center(vars, gen_coord(vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2), vars->win_size.y / 2, (1 / dist(vars->player.pos.x, vars->player.pos.y, vars->mult_positions[i].x, vars->mult_positions[i].y, angle)) *100 , gen_color(100,100,100,0)));
				}
				else if (( angle + (M_PI * 2.0)) > vars->start && (angle + (M_PI * 2.0)) < vars->end)
				{
					dangle = vars->end - (angle + (M_PI * 2.0));
					screen_x = vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2);
					if (screen_x < vars->win_size.x && screen_x > 0 && vars->rays[screen_x].dist > dist_players)
						draw_square_texture_center(vars, gen_coord(screen_x, vars->win_size.y / 2, (1 / dist_players) * (vars->win_size.y / 2), gen_color(100,100,100,0)), get_texture(vars, "oui", 0), dist_players);	
					// draw_square_center(vars, gen_coord(vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2), vars->win_size.y / 2, (1 / dist(vars->player.pos.x, vars->player.pos.y, vars->mult_positions[i].x, vars->mult_positions[i].y, angle)) *100 , gen_color(100,100,100,0)));	
				}
			}
		}
	}
}

void	draw_square_center(t_vars *vars, t_coord p)
{
	int	dy;
	int	dx;

	dy = p.y - p.z / 2;
	while (++dy < p.y + p.z / 2)
	{
		dx = p.x - p.z / 2;
		while (++dx < p.x + p.z / 2)
			if (is_in_window(vars, dx, dy))
				pixel_put(vars->img, dx,
						dy, to_rgb(p.c, 0));
	}
}

void	draw_square(t_vars *vars, t_coord p)
{
	int	dy;
	int	dx;

	dy = p.y;
	while (++dy < p.y + p.z)
	{
		dx = p.x;
		while (++dx < p.x + p.z)
			if (is_in_window(vars, dx, dy))
				pixel_put(vars->img, dx,
						dy, to_rgb(p.c, 0));
	}
}

void	draw_2d_enemies(t_vars *vars, int size)
{
	int	i;

	i = -1;
	while (++i < vars->n_enemies)
	{
		if (vars->enemies[i].lives > 0)
		{
			draw_square_center(vars,
				gen_coord(vars->enemies[i].pos.x * size + size, vars->enemies[i].pos.y * size + size, size / 2,
				gen_color(0, 0, 255, 0)));
		}
	}
}

void	draw_multi(t_vars *vars, int size)
{
	int	i;

	i = -1;
	while (++i < vars->mult_n_players && i < MAX_CLIENT)
	{
		if (i != vars->mult_id && vars->mult_positions[i].x > 0 && vars->mult_positions[i].y > 0)
			draw_square_center(vars,
				gen_coord(vars->mult_positions[i].x * size + size, vars->mult_positions[i].y * size + size, size / 2,
				gen_color(255, 255, 255, 0)));
	}
}

void	draw_bullets(t_vars *vars, int size)
{
	int		i;
	double	angle;
	double	dist_bullet;
	double	dangle;
	int		screen_x;

	i = -1;
	while (++i < MAX_CLIENT)
	{
		if (vars->bullets[i].pos.x >= 0)
			draw_square_center(vars,
				gen_coord(vars->bullets[i].pos.x * size + size, vars->bullets[i].pos.y * size + size, size / 2,
				gen_color(0, 255, 0, 0)));
	}

	i = -1;
	while (++i < MAX_CLIENT)
	{
		if (vars->bullets[i].pos.x > 0.0)
		{
			angle = atan2((vars->player.pos.y - vars->bullets[i].pos.y), (vars->player.pos.x - vars->bullets[i].pos.x));
			if (angle < 0)
				angle = M_PI * 2 + angle;
			angle =  angle + M_PI;
			angle = fmod(angle, M_PI * 2);
			// printf("player%d:%f|%f|%f\\%f\n",i,vars->start,angle,vars->end, angle + (M_PI * 2.0));
			dist_bullet = dist(vars->player.pos.x, vars->player.pos.y, vars->bullets[i].pos.x, vars->bullets[i].pos.y, angle);
			if (angle > vars->start && angle < vars->end)
			{
				dangle = vars->end - angle;
				screen_x = vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2);
				if (screen_x < vars->win_size.x && screen_x > 0 && vars->rays[screen_x].dist > dist_bullet)
					// draw_square_center(vars, gen_coord(screen_x, vars->win_size.y / 2, (1 / dist_bullet) * (vars->win_size.y / 2) * .2, gen_color(100,100,100,0)));
					draw_square_texture_center(vars, gen_coord(screen_x, vars->win_size.y / 2, (1 / dist_bullet) * (vars->win_size.y / 2) * .2, gen_color(100,100,100,0)), get_texture(vars, "bullet", 0), dist_bullet);
			}
			else if (( angle + (M_PI * 2.0)) > vars->start && (angle + (M_PI * 2.0)) < vars->end)
			{
				dangle = vars->end - (angle + (M_PI * 2.0));
				screen_x = vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2);
				if (screen_x < vars->win_size.x && screen_x > 0 && vars->rays[screen_x].dist > dist_bullet)
					// draw_square_center(vars, gen_coord(screen_x, vars->win_size.y / 2, (1 / dist_bullet) * (vars->win_size.y / 2) * .2, gen_color(100,100,100,0)));	
					draw_square_texture_center(vars, gen_coord(screen_x, vars->win_size.y / 2, (1 / dist_bullet) * (vars->win_size.y / 2) * .2, gen_color(100,100,100,0)), get_texture(vars, "bullet", 0), dist_bullet);
			}
		}
	}
}

void	shade_floor_ceil(t_vars *vars)
{
	// int	i;

	// i = -1;
	// while (++i < vars->win_size.y * 2)
	// {
	// 	//ft_int_memset(vars->img->addr + i * vars->win_size.x, to_rgb(vars->textures.c, 0), vars->win_size.x);
	// 	ft_int_memset(vars->img->addr + i * vars->win_size.x, add_shade(vars, to_rgb(vars->textures.c, 0), i / 10), vars->win_size.x);
	// }
	// while (i < vars->win_size.y * 4 - 1)
	// {
	// 	ft_int_memset(vars->img->addr + i * vars->win_size.x, add_shade(vars, to_rgb(vars->textures.f, 0), 255 / i), vars->win_size.x);
	// 	i++;
	// }
	double	ceiling;

	ceiling = 1.0 - (vars->player.rot.y + vars->win_size.y / 2) / vars->win_size.y;
	if (ceiling < 0.0)
		ceiling = 0.0;
	// printf("%.2f\n", vars->win_size.y - ceiling * vars->win_size.y);
	ft_int_memset(vars->img->addr,
		to_rgb(vars->f, 0), vars->win_size.y * vars->win_size.x);
	ft_int_memset(vars->img->addr, to_rgb(vars->c, 0),  vars->win_size.y * ceiling * vars->win_size.x);
	// ft_int_memset(vars->img->addr + (int)(ceiling * vars->win_size.y * vars->img->line_length),
	// 	to_rgb(vars->f, 0), (vars->win_size.y - ceiling * vars->win_size.y) * vars->win_size.x);
}

int	check_enemy_nearby(t_vars *vars, t_vector2 *bullet_pos)
{
	int		i;
	double	hitbox;

	i = -1;
	hitbox = .3;
	while (++i < vars->n_enemies)
	{
		if (vars->enemies[i].lives > 0)
		{
			// printf("%.2f %.2f	%.2f %.2f\n", bullet_pos->x, bullet_pos->y, vars->enemies[i].pos.x, vars->enemies[i].pos.y);
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
	int			hit;
	t_vector2	new_pos;

	i = -1;
	while (++i < MAX_BULLETS)
	{
		if (vars->bullets[i].pos.x > 0)
		{
			hit = 0;
			new_pos.x = vars->bullets[i].pos.x + vars->bullets[i].delta.x * .5 * vars->delta_time_render * 25.0;
			new_pos.y = vars->bullets[i].pos.y + vars->bullets[i].delta.y * .5 * vars->delta_time_render * 25.0;
			if (((int)new_pos.x >= 0 && (int)new_pos.y >= 0 && (int)new_pos.x < vars->size.x && (int)new_pos.y < vars->size.y) && vars->map[(int)new_pos.x + (int)vars->bullets[i].pos.y * vars->size.x] != 'C'
				&& vars->map[(int)new_pos.x + (int)vars->bullets[i].pos.y * vars->size.x] != '1')
				vars->bullets[i].pos.x = new_pos.x;
			else
				hit = 1;
			// printf("%d\n", (int)vars->bullets[i].pos.x);
			if (!hit && vars->map[(int)vars->bullets[i].pos.x + (int)new_pos.y * vars->size.x] != 'C'
				&& vars->map[(int)vars->bullets[i].pos.x + (int)new_pos.y * vars->size.x] != '1')
				vars->bullets[i].pos.y = new_pos.y;
			else
				hit = 1;
			if (check_enemy_nearby(vars, &vars->bullets[i].pos))
			{
				hit = 1;
				printf("HIT ENEMY\n");
			}
			if (hit)
				vars->bullets[i].pos.x = -1;
			// printf("%.2f %.2f	%.2f %.2f\n", vars->bullets[i].pos.x, vars->bullets[i].pos.y, vars->bullets[i].delta.x, vars->bullets[i].delta.y);
		}
	}
}

void	end_game(t_vars *vars)
{
	vars->ui = 10;
	draw_easy_texture(vars, gen_coord(vars->win_size.x / 2, vars->win_size.y / 2, vars->win_size.y / 2, gen_color(0, 0, 0, 0)), get_texture(vars, "end", 0));
}

int	try_attack(t_vars *vars, t_enemy *enemy)
{
	time_t	attack_ts;

	attack_ts = gettime(vars->n1);
	if (attack_ts - enemy->last_attack < 1000)
		return (0);
	vars->player.lives--;
	if (vars->player.lives <= 0)
		end_game(vars);
	return (1);
}

void	process_enemies(t_vars *vars)
{
	int		i;
	double	angle;
	double	dist_enemy;
	// double	dangle;
	// int		screen_x;
	t_vector2	new_pos;
	t_ray	ray;

	i = -1;
	while (++i < vars->n_enemies)
	{
		if (vars->enemies[i].lives > 0)
		{
			angle = atan2((vars->enemies[i].pos.y - vars->player.pos.y), (vars->enemies[i].pos.x - vars->player.pos.x));
			if (angle < 0)
				angle = M_PI * 2 + angle;
			angle =  angle + M_PI;
			angle = fmod(angle, M_PI * 2);
			printf("player%d:%f|%f|%f\\%f\n",i,vars->start,angle,vars->end, angle + (M_PI * 2.0));
			dist_enemy = dist(vars->enemies[i].pos.x, vars->enemies[i].pos.y, vars->player.pos.x, vars->player.pos.y, angle);
			// if (dist_enemy < .8 && try_attack(vars, &vars->enemies[i]))
			// 	return ;
			ray.ra2 = angle;
			ray.start_pos.x = vars->enemies[i].pos.x;
			ray.start_pos.y = vars->enemies[i].pos.y;
			calc_ray(vars, &ray);
			if (dist_enemy < ray.dist)
			{
				new_pos.x = vars->enemies[i].pos.x + (.08 - .16 * (vars->player.pos.x < vars->enemies[i].pos.x))* vars->delta_time * 20.0;
				new_pos.y = vars->enemies[i].pos.y + (.08 - .16 * (vars->player.pos.y < vars->enemies[i].pos.y)) * vars->delta_time * 20.0;
				change_case(vars, new_pos.x, new_pos.y, &vars->enemies[i].pos);
				vars->enemies[i].pos.x = new_pos.x;
				vars->enemies[i].pos.y = new_pos.y;
			}
		}
	}
}

void	gen_bullet(t_vars *vars)
{
	int		i;
	time_t	cooldown;

	cooldown = gettime(vars->n1);
	if (cooldown - vars->bullet_cooldown < 400
		|| vars->mult_fd || !vars->clicking)
		return ;
	vars->bullet_cooldown = cooldown;
	i = -1;
	while (++i < MAX_BULLETS)
		if (vars->bullets[i].pos.x < 0)
			break;
	if (i == MAX_BULLETS)
		return ;
	vars->bullets[i].pos.x = vars->player.pos.x;
	vars->bullets[i].pos.y = vars->player.pos.y;
	vars->bullets[i].delta.x = cos(vars->player.rot.x);
	vars->bullets[i].delta.y = sin(vars->player.rot.x);
	// printf("%.2f %.2f\n", vars->player.delta.x, vars->player.delta.y);
}

void	draw_hud(t_vars *vars)
{
	// Cursor
	draw_square_center(vars, gen_coord(vars->win_size.x / 2, vars->win_size.y / 2, 4, gen_color(255, 255, 255, 0)));
	draw_square_center(vars, gen_coord(vars->win_size.x / 2, vars->win_size.y / 2, 2, gen_color(0, 0, 0, 0)));
	draw_easy_texture(vars, gen_coord(vars->win_size.x / 2, vars->win_size.y / 2, vars->win_size.y, gen_color(0, 0, 0, 0)), get_texture(vars, "hud", 0));
}

void	render(t_vars *vars)
{
	t_data	*img;

	img = vars->img;
	vars->img = vars->img2;
	int		x;
	int		y;
	time_t	jump_time;

	void *tmp;

	tmp = vars->img;
	vars->img = vars->img2;
	vars->img2 = tmp;
	mlx_mouse_get_pos(vars->win, &x, &y);
	// printf("%.2f\n", vars->player.rot.y);
	if (!vars->ui)
	{
		// printf("MOUSE %d %d\n", x, y);
		if (x > vars->win_size.x / 2)
			rotate_player_x(vars, x - vars->win_size.x / 2);
		else if (x < vars->win_size.x / 2)
			rotate_player_x(vars, x - vars->win_size.x / 2);
		if (vars->player.rot.y + (y - vars->win_size.y / 2)
			* vars->settings.y_ratio_mouse_speed > -vars->win_size.y / 2
			&& vars->player.rot.y + (y - vars->win_size.y / 2) * vars->settings.y_ratio_mouse_speed < vars->win_size.y / 2)
			vars->player.rot.y += (y - vars->win_size.y / 2) * vars->settings.y_ratio_mouse_speed;
		mlx_mouse_move(vars->win, vars->win_size.x / 2,  vars->win_size.y / 2);
		// if (vars->player.rot.y + jump_height < vars->win_size.y && vars->player.rot.y + jump_height > 0)
		// 	vars->player.rot.y += 
	}
	gen_bullet(vars);
	jump_time = gettime(vars->n1) - vars->jump;
	if (jump_time < 1000)
		vars->jump_height = -(((-1.0 / 1000.0) * ((int)jump_time * (int)jump_time) + .0) + (int)jump_time) * 1.5;
	else
		vars->jump_height = 0.0;
	shade_floor_ceil(vars);
	project_rays(vars);
	draw_other_players(vars);
	process_enemies(vars);
	draw_enemies(vars);
	//test_rays(vars);
	draw_2d_map(vars, vars->min_map_mult);
	show_player(vars, vars->min_map_mult);
	process_bullets(vars);
	draw_bullets(vars, vars->min_map_mult);
	if (vars->mult_fd)
		draw_multi(vars, vars->min_map_mult);
	draw_2d_enemies(vars, vars->min_map_mult);
	draw_hud(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	// vars->img = img;
}
