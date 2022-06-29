/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:00:14 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/25 14:32:28 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	project_rays_draw(t_vars *vars)
{
	int			i;

	i = 0;
	while (i < vars->win_size.x)
	{
		if (vars->rays[i].side == 0)
		{
			if (vars->rays[i].ra2 > M_PI)
				line_texture(vars, i, "no");
			else
				line_texture(vars, i, "so");
		}
		else
		{
			if (vars->rays[i].ra2 > M_PI_2 && vars->rays[i].ra2 < M_PI_2 + M_PI)
				line_texture(vars, i, "we");
			else
				line_texture(vars, i, "ea");
		}
		i += 1;
	}
}

void	project_rays(t_vars *vars)
{
	int			i;
	double		ca;

	i = -1;
	vars->start = fmod(vars->player.rot.x - M_PI_4 + (M_2PI), M_2PI);
	vars->end = fmod(vars->player.rot.x + M_PI_4 + (M_2PI), M_2PI);
	if (vars->start > vars->end)
		vars->end += (M_2PI);
	vars->rotmpi = vars->player.rot.x + (M_2PI);
	while (++i < vars->win_size.x)
	{
		vars->rays[i].ra2 = fmod(vars->rotmpi
				- atan(1.0 - (vars->tx * i)), M_2PI);
		vars->rays[i].start_pos.x = vars->player.pos.x;
		vars->rays[i].start_pos.y = vars->player.pos.y;
		calc_ray(vars, &vars->rays[i]);
		ca = vars->player.rot.x - vars->rays[i].ra2;
		if (ca < 0 || ca > M_2PI)
			ca += M_2PI * ((ca > M_2PI) * -1);
		vars->rays[i].dist *= cos(ca);
	}
	project_rays_draw(vars);
}
