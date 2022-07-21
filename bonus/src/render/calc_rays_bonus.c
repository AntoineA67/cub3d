/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rays_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:53:05 by qroussea          #+#    #+#             */
/*   Updated: 2022/07/21 15:33:47 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calc_t_vector2(t_vector2 *dis, t_vector2 *rv, t_vector2 o, t_vars *vars)
{
	int			mp;
	int			dof;

	dof = 0;
	while (dof < vars->max_size)
	{
		if (rv->y > -0.000001 && rv->x >= -0.000001
			&& rv->y <= vars->size.y && rv->x <= vars->size.x)
		{
			mp = (int)rv->y * vars->size.x + (int)rv->x;
			if (mp < vars->size.z && mp >= 0
				&& (vars->map[mp] == '1' || vars->map[mp] == 'C'))
			{
				dis->x = rv->x;
				dis->y = rv->y;
				return ;
			}
		}
		rv->x += o.x;
		rv->y += o.y;
		dof += 1;
	}
	dis->x = rv->x;
	dis->y = rv->y;
}

void	calc_v_rays(t_vars *vars, t_vector2 *disV, t_ray *r, t_vector2 *rv)
{
	t_vector2	o;

	ft_bzero(&o, sizeof(t_vector2));
	if (r->ra2 > M_PI)
	{
		rv->y = (int)floorf(r->start_pos.y) - 0.0000000001;
		rv->x = (r->start_pos.y - rv->y) * (-1. / tan(r->ra2)) + r->start_pos.x;
		o.y = -1.0;
		o.x = 1.0 * (-1.0 / tan(r->ra2));
	}
	if (r->ra2 == 0.0 || r->ra2 == M_PI)
	{
		rv->x = r->start_pos.x;
		rv->y = r->start_pos.y;
	}
	if (r->ra2 < M_PI)
	{
		rv->y = (int)floorf(r->start_pos.y) + 1 ;
		rv->x = (r->start_pos.y - rv->y) * (-1. / tan(r->ra2)) + r->start_pos.x;
		o.y = 1.0;
		o.x = -1.0 * (-1.0 / tan(r->ra2));
	}
	calc_t_vector2(disV, rv, o, vars);
}

void	calc_h_rays(t_vars *vars, t_vector2 *disH, t_ray *r, t_vector2 *rv)
{
	t_vector2	o;

	ft_bzero(&o, sizeof(t_vector2));
	if (r->ra2 > M_PI_2 && r->ra2 < M_PI_2 * 3.0)
	{
		rv->x = (int)floorf(r->start_pos.x) - 0.00000001;
		rv->y = (r->start_pos.x - rv->x) * (-tan(r->ra2)) + r->start_pos.y;
		o.x = -1.0;
		o.y = 1.0 * (-tan(r->ra2));
	}
	if (r->ra2 == M_PI_2 || r->ra2 == M_PI_2 * 3.0)
	{
		rv->x = r->start_pos.x;
		rv->y = r->start_pos.y;
	}
	if (r->ra2 > M_PI_2 * 3.0 || r->ra2 < M_PI_2)
	{
		rv->x = (int)floorf(r->start_pos.x) + 1;
		rv->y = (r->start_pos.x - rv->x) * (-tan(r->ra2)) + r->start_pos.y;
		o.x = 1.0;
		o.y = -1.0 * (-tan(r->ra2));
	}
	calc_t_vector2(disH, rv, o, vars);
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
