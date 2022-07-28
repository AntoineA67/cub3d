/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:54:13 by arangoni          #+#    #+#             */
/*   Updated: 2022/07/28 17:51:42 by arangoni         ###   ########.fr       */
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

void	mouse_rotate(t_vars *vars)
{
	int		x;
	int		y;

	mlx_mouse_get_pos(vars->win, &x, &y);
	if (x > vars->win_size.x / 2)
		rotate_player_x(vars, x - vars->win_size.x / 2);
	else if (x < vars->win_size.x / 2)
		rotate_player_x(vars, x - vars->win_size.x / 2);
	if (vars->player.rot.y + (y - vars->win_size.y / 2) > -vars->win_size.y / 2
		&& vars->player.rot.y
		+ (y - vars->win_size.y / 2) < vars->win_size.y / 2)
		vars->player.rot.y += (y - vars->win_size.y / 2);
	mlx_mouse_move(vars->win, vars->win_size.x / 2, vars->win_size.y / 2);
}

void	render(t_vars *vars)
{
	void	*tmp;

	tmp = vars->img;
	vars->img = vars->img2;
	vars->img2 = tmp;
	vars->dt++;
	if (vars->dt == INT32_MAX)
		vars->dt = 0;
	mouse_rotate(vars);
	shade_floor_ceil(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	project_rays(vars);
	draw_mini_circle(vars, 0, -1, vars->img);
	show_player(vars);
	mlx_mouse_hide();
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}
