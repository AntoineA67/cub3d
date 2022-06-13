/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:00:14 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/11 12:39:03 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	get_aox(t_vars *vars, int cas, int i)
{
	int	buff;

	if (!cas)
		buff = (int)vars->rays[i].ry + 1;
	else if (cas == 1)
		buff = (int)vars->rays[i].ry - 1;

	if (vars->rays[i].rx - (int)vars->rays[i].rx < .5 && ((int)vars->rays[i].rx - 1) >= 0 && ((int)vars->rays[i].rx - 1) < vars->size.x
		&& buff >= 0 && buff < vars->size.y
		&& (vars->map[(int)vars->rays[i].rx - 1 + buff * vars->size.x] == '1'
		|| vars->map[(int)vars->rays[i].rx - 1 + buff * vars->size.x] == 'C'))
		return (1.0 - (vars->rays[i].rx - (int)vars->rays[i].rx) * 2.0);
	else if (vars->rays[i].rx - (int)vars->rays[i].rx > .5 && ((int)vars->rays[i].rx + 1) >= 0 && ((int)vars->rays[i].rx + 1) < vars->size.x
		&& buff >= 0 && buff < vars->size.y
		&& (vars->map[(int)vars->rays[i].rx + 1 + buff * vars->size.x] == '1'
		|| vars->map[(int)vars->rays[i].rx + 1 + buff * vars->size.x] == 'C'))
		return ((vars->rays[i].rx - (int)vars->rays[i].rx) * 2.0 - 1.0);
	return (0);
}

double	get_aoy(t_vars *vars, int cas, int i)
{
	int	buff2;

	if (!cas)
	{
		buff2 = (int)vars->rays[i].rx + 1;
	}
	else if (cas == 1)
	{
		buff2 = (int)vars->rays[i].rx - 1;
	}
	if (vars->rays[i].ry - (int)vars->rays[i].ry < .5 && (buff2) >= 0 && (buff2) < vars->size.x
		&& ((int)vars->rays[i].ry - 1) >= 0 && ((int)vars->rays[i].ry - 1) < vars->size.y
		&& (vars->map[buff2 + ((int)vars->rays[i].ry - 1) * vars->size.x] == '1'
		|| vars->map[buff2 + ((int)vars->rays[i].ry - 1) * vars->size.x] == 'C'))
		return (1.0 - (vars->rays[i].ry - (int)vars->rays[i].ry) * 2.0);
	else if (vars->rays[i].ry - (int)vars->rays[i].ry > .5 && (buff2) >= 0 && (buff2) < vars->size.x
		&& ((int)vars->rays[i].ry + 1) >= 0 && ((int)vars->rays[i].ry + 1) < vars->size.y
		&& (vars->map[buff2 + ((int)vars->rays[i].ry + 1) * vars->size.x] == '1'
		|| vars->map[buff2 + ((int)vars->rays[i].ry + 1) * vars->size.x] == 'C'))
		return  ((vars->rays[i].ry - (int)vars->rays[i].ry) * 2.0 - 1.0);
	return (0);
}

void	project_rays_draw(t_vars *vars)
{
	int			i;

	i = 0;
	while (i < vars->win_size.x)
	{
		if (vars->rays[i].side == 0)
		{
			if (vars->rays[i].ra2 > M_PI)
				line_texture(vars, i, 0, get_aox(vars, 0, i));
			else
				line_texture(vars, i, 1, get_aox(vars, 1, i));
		}
		else
		{
			if (vars->rays[i].ra2 > M_PI_2 && vars->rays[i].ra2 < M_PI_2 + M_PI)
				line_texture(vars, i, 2, get_aoy(vars, 0, i));
			else
				line_texture(vars, i, 3, get_aoy(vars, 1, i));
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
		if (i == vars->win_size.x * 0.5)
			vars->rays[i].ra2 = vars->player.rot.x;
		else
			vars->rays[i].ra2 = fmod(vars->rotmpi - atan(1.0 - (vars->tx * i)), M_2PI);
		vars->rays[i].start_pos.x = vars->player.pos.x;
		vars->rays[i].start_pos.y = vars->player.pos.y;
		calc_ray(vars, &vars->rays[i]);
		ca = vars->player.rot.x - vars->rays[i].ra2;
		if (ca < 0)
			ca += M_2PI;
		if (ca > M_2PI)
			ca -= M_2PI;
		vars->rays[i].dist *= cos(ca);
	}
	project_rays_draw(vars);
}
