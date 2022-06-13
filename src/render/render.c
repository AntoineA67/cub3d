/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:54:13 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/13 14:01:55 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
				dist_players = dist(vars->player.pos.x, vars->player.pos.y, vars->mult_positions[i].x, vars->mult_positions[i].y);
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

void	draw_multi(t_vars *vars, int size)
{
	int	i;

	i = -1;
	while (++i < vars->mult_n_players && i < MAX_CLIENT)
	{
		if (i != vars->mult_id && vars->mult_positions[i].x > 0
			&& vars->mult_positions[i].y > 0)
			draw_square_center(vars,
				gen_coord(vars->mult_positions[i].x * size + size,
					vars->mult_positions[i].y * size + size, size / 2,
					gen_color(255, 255, 255, 0)));
	}
}

void	shade_floor_ceil(t_vars *vars)
{
	double			ceil;
	unsigned int	*i;
	int				max;

	ceil = 1.0 - (vars->player.rot.y + vars->win_size.y / 2) / vars->win_size.y;
	if (ceil < 0.0)
		ceil = 0.0;
	i = (unsigned int *)vars->img->addr;
	max = vars->win_size.y * vars->win_size.x;
	while (i - (unsigned int *)vars->img->addr < max * ceil)
	{
		*i = to_rgb(vars->c, 0);
		i++;
	}
	while (i - (unsigned int *)vars->img->addr < max)
	{
		*i = to_rgb(vars->f, 0);
		i++;
	}
}

void	draw_hud(t_vars *vars)
{
	int		i;
	char	*hud;
	time_t	cooldown;

	draw_square_center(vars, gen_coord(vars->win_size.x / 2,
			vars->win_size.y / 2, 4, gen_color(255, 255, 255, 0)));
	draw_square_center(vars, gen_coord(vars->win_size.x / 2,
			vars->win_size.y / 2, 2, gen_color(0, 0, 0, 0)));
	cooldown = gettime(vars->n1);
	if (cooldown - vars->bullet_cooldown < 140)
		hud = "hud1";
	else
		hud = "hud";
	draw_easy_texture(vars, gen_coord(vars->win_size.x / 2,
			vars->win_size.y - 50,
			1000, gen_color(0, 0, 0, 0)), get_texture(vars, hud, 0));
	i = -1;
	while (++i < vars->player.lives)
		draw_easy_texture(vars, gen_coord(60 + i * 40, vars->win_size.y - 50,
				32, gen_color(0, 0, 0, 0)), get_texture(vars, "hp", 0));
}

void	mouse_rotate(t_vars *vars)
{
	int		x;
	int		y;

	mlx_mouse_get_pos(vars->win, &x, &y);
	if (x > vars->win_size.x / 2)
		rotate_player_x(vars, x - vars->win_size.x / 2);
	else if (x < vars->win_size.x / 2)
		rotate_player_x(vars, x - vars->win_size.x / 2);
	if (vars->player.rot.y + (y - vars->win_size.y / 2)
		* vars->settings.y_ratio_mouse_speed > -vars->win_size.y / 2
		&& vars->player.rot.y + (y - vars->win_size.y / 2)
		* vars->settings.y_ratio_mouse_speed < vars->win_size.y / 2)
		vars->player.rot.y += (y - vars->win_size.y / 2)
			* vars->settings.y_ratio_mouse_speed;
	mlx_mouse_move(vars->win, vars->win_size.x / 2, vars->win_size.y / 2);
}

void	render(t_vars *vars)
{
	t_data	*img;
	time_t	jump_time;
	void	*tmp;

	img = vars->img;
	vars->img = vars->img2;
	tmp = vars->img;
	vars->img = vars->img2;
	vars->img2 = tmp;
	mouse_rotate(vars);
	if (check_end_game(vars))
		return ;
	gen_bullet(vars);
	jump_time = gettime(vars->n1) - vars->jump;
	if (jump_time < 1000)
		vars->jump_height = -(((-1.0 / 1000.0) * ((int)jump_time * (int)jump_time) + .0) + (int)jump_time) * 1.5;
	else
		vars->jump_height = 0.0;
	shade_floor_ceil(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	project_rays(vars);
	draw_other_players(vars);
	process_enemies(vars);
	draw_enemies(vars);
	draw_2d_map(vars, vars->min_map_mult);
	show_player(vars, vars->min_map_mult);
	process_bullets(vars);
	draw_bullets(vars);
	if (vars->mult_fd)
		draw_multi(vars, vars->min_map_mult);
	//draw_2d_enemies(vars, vars->min_map_mult);
	draw_hud(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}
