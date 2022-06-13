/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:53:05 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/11 12:13:11 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calc_vertical_rays(t_vars *vars, t_vector2 *disV, t_ray *r, t_vector2 *rv)
{
	int			mp;
	int			dof;
	double		aTan;
	double		yo;
	double		xo;

	dof = 0;
	aTan = -1.0 / tan(r->ra2);
	if (r->ra2 > M_PI) //looking down
	{
		rv->y = (int)r->start_pos.y - .00001;
		rv->x = (r->start_pos.y - rv->y) * aTan + r->start_pos.x;
		yo = -1.0;
		xo = 1.0 * aTan;
	}
	if (r->ra2 < M_PI && r->ra2 != 0) //looking up
	{
		rv->y = (int)r->start_pos.y + 1.0;
		rv->x = (r->start_pos.y - rv->y) * aTan + r->start_pos.x;
		yo = 1.0;
		xo = -1.0 * aTan;
	}
	if (r->ra2 == 0.0 || r->ra2 == M_PI)//looking straight left or right
	{
		rv->x = r->start_pos.x;
		rv->y = r->start_pos.y;
		dof = vars->max_size;
	}
	while (dof < vars->max_size)
	{
		mp = (int)rv->y * vars->size.x + (int)rv->x;
		if (mp < vars->size.z && mp >= 0 && (vars->map[mp] == '1' || vars->map[mp] == 'C'))
			dof = vars->max_size;
		else
		{
			rv->x += xo;
			rv->y += yo;
			dof += 1;
		}
	}
	disV->x = rv->x;
	disV->y = rv->y;
}

void	calc_horizontal_rays(t_vars *vars, t_vector2 *disH, t_ray *r, t_vector2 *rv)
{
	int			mp;
	int			dof;
	double		nTan;
	double		yo;
	double		xo;

	dof = 0;
	nTan = -tan(r->ra2);
	if (r->ra2 > M_PI_2 && r->ra2 < M_PI_2 * 3.0) //looking left
	{
		rv->x = (int)r->start_pos.x - .00001;
		rv->y = (r->start_pos.x - rv->x) * nTan + r->start_pos.y;
		xo = -1.0;
		yo = 1.0 * nTan;
	}
	if (r->ra2 > M_PI_2 * 3.0 || r->ra2 < M_PI_2) //looking right
	{
		rv->x = (int)r->start_pos.x + 1.0;
		rv->y = (r->start_pos.x - rv->x) * nTan + r->start_pos.y;
		xo = 1.0;
		yo = -1.0 * nTan;
	}
	if (r->ra2 == M_PI_2 || r->ra2 == M_PI_2 * 3.0)//looking straight left or right
	{
		rv->x = r->start_pos.x;
		rv->y = r->start_pos.y;
		dof = vars->max_size;
	}
	while (dof < vars->max_size)
	{
		mp = (int)rv->y * vars->size.x + (int)rv->x;
		if (mp < vars->size.z && mp >= 0 && (vars->map[mp] == '1' || vars->map[mp] == 'C'))
			dof = vars->max_size;
		else
		{
			rv->x += xo;
			rv->y += yo;
			dof += 1;
		}
	}
	disH->x = rv->x;
	disH->y = rv->y;
}

void	calc_ray(t_vars *vars, t_ray *r)
{
	double		min_dist;
	t_vector2	disV;
	t_vector2	disH;
	t_vector2	rv;

	rv.x = 0;
	rv.y = 0;
	calc_vertical_rays(vars, &disV, r, &rv);
	calc_horizontal_rays(vars, &disH, r, &rv);
	r->side = 1;
	if (dist(r->start_pos.x, r->start_pos.y, disV.x, disV.y) <
		dist(r->start_pos.x, r->start_pos.y, disH.x, disH.y))
	{
		//HIT VERTICAL
		rv.x = disV.x;
		rv.y = disV.y;
		r->side = 0;
	}
	min_dist = dist(r->start_pos.x, r->start_pos.y, rv.x, rv.y);
	r->dist = min_dist;
	r->ry = rv.y;
	r->rx = rv.x;
}
