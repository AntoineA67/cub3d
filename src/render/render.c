/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:54:13 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/14 15:34:12 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	jumpproc(t_vars *vars)
{
	time_t	jump_time;

	jump_time = gettime(vars->n1) - vars->jump;
	if (jump_time < 1000)
		vars->jump_height = -(((-1.0 / 1000.0)
					* ((int)jump_time * (int)jump_time) + .0)
				+ (int)jump_time) * 1.5;
	else
		vars->jump_height = 0.0;
}

void	render(t_vars *vars)
{
	void	*tmp;

	tmp = vars->img;
	vars->img = vars->img2;
	vars->img2 = tmp;
	mouse_rotate(vars);
	if (check_end_game(vars))
		return ;
	gen_bullet(vars);
	jumpproc(vars);
	shade_floor_ceil(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	project_rays(vars);
	process_enemies(vars);
	draw_2d_map(vars, vars->min_map_mult);
	show_player(vars, vars->min_map_mult);
	process_bullets(vars);
	draw_2d_enemies(vars, vars->min_map_mult);
	draw_hud(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}
