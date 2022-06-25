/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:54:13 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/25 14:22:02 by qroussea         ###   ########lyon.fr   */
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

void	render(t_vars *vars)
{
	void	*tmp;

	tmp = vars->img;
	vars->img = vars->img2;
	vars->img2 = tmp;
	shade_floor_ceil(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	project_rays(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}
