/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:53:05 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/13 15:03:55 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calc_t_vector2(t_vector2 *dis, t_vector2 *rv, int dof, double xo, double yo, t_vars *vars)
{
	int			mp;

	while (dof < vars->max_size)
	{
		mp = (int)rv->y * vars->size.x + (int)rv->x;
		if (mp < vars->size.z && mp >= 0
			&& (vars->map[mp] == '1' || vars->map[mp] == 'C'))
			dof = vars->max_size;
		else
		{
			rv->x += xo;
			rv->y += yo;
			dof += 1;
		}
	}
	dis->x = rv->x;
	dis->y = rv->y;
}

void	calc_v_rays(t_vars *vars, t_vector2 *disV, t_ray *r, t_vector2 *rv)
{
	int			dof;
	double		yo;
	double		xo;

	dof = 0;
	if (r->ra2 > M_PI)
	{
		rv->y = (int)r->start_pos.y - .00001;
		rv->x = (r->start_pos.y - rv->y) * (-1. / tan(r->ra2)) + r->start_pos.x;
		yo = -1.0;
		xo = 1.0 * (-1.0 / tan(r->ra2));
	}
	if (r->ra2 < M_PI && r->ra2 != 0)
	{
		rv->y = (int)r->start_pos.y + 1.0;
		rv->x = (r->start_pos.y - rv->y) * (-1. / tan(r->ra2)) + r->start_pos.x;
		yo = 1.0;
		xo = -1.0 * (-1.0 / tan(r->ra2));
	}
	if (r->ra2 == 0.0 || r->ra2 == M_PI)
	{
		rv->x = r->start_pos.x;
		rv->y = r->start_pos.y;
		dof = vars->max_size;
	}
	calc_t_vector2(disV, rv, dof, xo, yo, vars);
}

void	calc_h_rays(t_vars *vars, t_vector2 *disH, t_ray *r, t_vector2 *rv)
{
	int			dof;
	double		yo;
	double		xo;

	dof = 0;
	if (r->ra2 > M_PI_2 && r->ra2 < M_PI_2 * 3.0)
	{
		rv->x = (int)r->start_pos.x - .00001;
		rv->y = (r->start_pos.x - rv->x) * (-tan(r->ra2)) + r->start_pos.y;
		xo = -1.0;
		yo = 1.0 * (-tan(r->ra2));
	}
	if (r->ra2 > M_PI_2 * 3.0 || r->ra2 < M_PI_2)
	{
		rv->x = (int)r->start_pos.x + 1.0;
		rv->y = (r->start_pos.x - rv->x) * (-tan(r->ra2)) + r->start_pos.y;
		xo = 1.0;
		yo = -1.0 * (-tan(r->ra2));
	}
	if (r->ra2 == M_PI_2 || r->ra2 == M_PI_2 * 3.0)
	{
		rv->x = r->start_pos.x;
		rv->y = r->start_pos.y;
		dof = vars->max_size;
	}
	calc_t_vector2(disH, rv, dof, xo, yo, vars);
}

void	calc_ray(t_vars *vars, t_ray *r)
{
	double		min_dist;
	t_vector2	disv;
	t_vector2	dish;
	t_vector2	rv;

	rv.x = 0;
	rv.y = 0;
	calc_v_rays(vars, &disv, r, &rv);
	calc_h_rays(vars, &dish, r, &rv);
	r->side = 1;
	if (dist(r->start_pos.x, r->start_pos.y, disv.x, disv.y)
		< dist(r->start_pos.x, r->start_pos.y, dish.x, dish.y))
	{
		rv.x = disv.x;
		rv.y = disv.y;
		r->side = 0;
	}
	min_dist = dist(r->start_pos.x, r->start_pos.y, rv.x, rv.y);
	r->dist = min_dist;
	r->ry = rv.y;
	r->rx = rv.x;
}
