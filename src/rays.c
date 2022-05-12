/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:00:14 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/12 16:57:26 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	calc_ray(t_vars *vars, t_ray *r)
{
	int			dof;
	int			mx;
	int			my;
	int			mp;
	double		ca; 
	double		aTan;
	double		nTan;
	double		ry;
	double		rx;
	double		yo;
	double		xo;
	double		min_dist;
	t_vector2	disV;
	t_vector2	disH;

	dof = 0;
	aTan = -1.0 / tan(r->ra2);
	if (r->ra2 > M_PI) //looking down
	{
		ry = (int)vars->player.pos.y - .00001;
		rx = (vars->player.pos.y - ry) * aTan + vars->player.pos.x;
		yo = -1.0;
		xo = 1.0 * aTan;
	}
	if (r->ra2 < M_PI && r->ra2 != 0) //looking up
	{
		ry = (int)vars->player.pos.y + 1.0;
		rx = (vars->player.pos.y - ry) * aTan + vars->player.pos.x;
		yo = 1.0;
		xo = -1.0 * aTan;
	}
	if (r->ra2 == 0.0 || r->ra2 == M_PI)//looking straight left or right
	{
		rx = vars->player.pos.x;
		ry = vars->player.pos.y;
		dof = vars->max_size;
	}
	while (dof < vars->max_size)
	{
		mx = (int)rx;
		my = (int)ry;
		mp = my * vars->size.x + mx;
		if (mp < vars->size.z && mp >= 0 && (vars->map[mp] == '1' || vars->map[mp] == 'C'))
			dof = vars->max_size;
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
	disV.x = rx;
	disV.y = ry;
	//Horizontal rays
	dof = 0;
	nTan = -tan(r->ra2);
	if (r->ra2 > M_PI_2 && r->ra2 < M_PI_2 * 3.0) //looking left
	{
		rx = (int)vars->player.pos.x - .00001;
		ry = (vars->player.pos.x - rx) * nTan + vars->player.pos.y;
		xo = -1.0;
		yo = 1.0 * nTan;
	}
	if (r->ra2 > M_PI_2 * 3.0 || r->ra2 < M_PI_2) //looking right
	{
		rx = (int)vars->player.pos.x + 1.0;
		ry = (vars->player.pos.x - rx) * nTan + vars->player.pos.y;
		xo = 1.0;
		yo = -1.0 * nTan;
	}
	if (r->ra2 == M_PI_2 || r->ra2 == M_PI_2 * 3.0)//looking straight left or right
	{
		rx = vars->player.pos.x;
		ry = vars->player.pos.y;
		dof = vars->max_size;
	}
	while (dof < vars->max_size)
	{
		mx = (int)rx;
		my = (int)ry;
		mp = my * vars->size.x + mx;
		if (mp < vars->size.z && mp >= 0 && (vars->map[mp] == '1' || vars->map[mp] == 'C'))
			dof = vars->max_size;
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
	disH.x = rx;
	disH.y = ry;
	r->side = 1;
	if (dist(vars->player.pos.x, vars->player.pos.y, disV.x, disV.y, r->ra2) <
		dist(vars->player.pos.x, vars->player.pos.y, disH.x, disH.y, r->ra2))
	{
		//HIT VERTICAL
		rx = disV.x;
		ry = disV.y;
		r->side = 0;
	}
	min_dist = dist(vars->player.pos.x, vars->player.pos.y, rx, ry, r->ra2);
	ca = vars->player.rot.x - r->ra2;
	if (ca < 0)
		ca += M_2PI;
	if (ca > M_2PI)
		ca -= M_2PI;
	min_dist *= cos(ca);
	r->dist = min_dist;
	r->ry = ry;
	r->rx = rx;
}


void	project_rays(t_vars *vars)
{
	int			i;
	// int			size;
	double		ao;
	// double		tx;

	i = -1;
	vars->start = fmod(vars->player.rot.x - M_PI_4 + (M_2PI) , M_2PI);
	vars->end = fmod(vars->player.rot.x + M_PI_4 + (M_2PI) , M_2PI);
	if (vars->start > vars->end)
		vars->end += (M_2PI);
	vars->rotmpi = vars->player.rot.x + (M_2PI);
	while (++i < vars->win_size.x)
	{
		if (i == vars->win_size.x / 2.0)
			vars->rays[i].ra2 = vars->player.rot.x;
		else
			vars->rays[i].ra2 = fmod(vars->rotmpi - atan(1.0 - (vars->tx * i)), M_2PI);
		calc_ray(vars, &vars->rays[i]);
	}
	i = -1;
	while (++i < vars->win_size.x)
	{
		ao = 0.0;
		if (vars->rays[i].side == 0)
		{
			// vars->rays[i] = dist(vars->player.pos.x, vars->player.pos.y, disV.x, disV.y, ra2);
			if (vars->rays[i].ra2 > M_PI)
			{
				// if (i == vars->win_size.x / 2)
				// 	printf("hit %d %d %.2f %.2f %c\n", (int)rx, (int)ry, rx - (int)rx, ry - (int)ry, 'N');
				if (vars->rays[i].rx - (int)vars->rays[i].rx < .5 && ((int)vars->rays[i].rx - 1) >= 0 && ((int)vars->rays[i].rx - 1) < vars->size.x
					&& ((int)vars->rays[i].ry + 1) >= 0 && ((int)vars->rays[i].ry + 1) < vars->size.y
					&& (vars->map[(int)vars->rays[i].rx - 1 + ((int)vars->rays[i].ry + 1) * vars->size.x] == '1'
					|| vars->map[(int)vars->rays[i].rx - 1 + ((int)vars->rays[i].ry + 1) * vars->size.x] == 'C'))
					ao = 1.0 - (vars->rays[i].rx - (int)vars->rays[i].rx) * 2.0;
				else if (vars->rays[i].rx - (int)vars->rays[i].rx > .5 && ((int)vars->rays[i].rx + 1) >= 0 && ((int)vars->rays[i].rx + 1) < vars->size.x
					&& ((int)vars->rays[i].ry + 1) >= 0 && ((int)vars->rays[i].ry + 1) < vars->size.y
					&& (vars->map[(int)vars->rays[i].rx + 1 + ((int)vars->rays[i].ry + 1) * vars->size.x] == '1'
					|| vars->map[(int)vars->rays[i].rx + 1 + ((int)vars->rays[i].ry + 1) * vars->size.x] == 'C'))
					ao = (vars->rays[i].rx - (int)vars->rays[i].rx) * 2.0 - 1.0;
				// line_texture(vars, i, (vars->rays[i].rx - (int)vars->rays[i].rx) * (get_texture(vars, "no", 0)->size.x + .0), get_texture(vars, "no", 0), min_dist, ao);
				line_texture(vars, i, (vars->rays[i].rx - (int)vars->rays[i].rx) * (get_animtexture(vars, "player", 0.2)->size.x + .0), get_animtexture(vars, "player", 0.2), vars->rays[i].dist, ao);
				//nord
			}
			else
			{
				// if (i == vars->win_size.x / 2)
				// 	printf("hit %d %d %.2f %.2f %c\n", (int)vars->rays[i].rx, (int)vars->rays[i].ry, vars->rays[i].rx - (int)vars->rays[i].rx, vars->rays[i].ry - (int)vars->rays[i].ry, 'S');
				if (vars->rays[i].rx - (int)vars->rays[i].rx < .5 && ((int)vars->rays[i].rx - 1) >= 0 && ((int)vars->rays[i].rx - 1) < vars->size.x
					&& ((int)vars->rays[i].ry - 1) >= 0 && ((int)vars->rays[i].ry - 1) < vars->size.y
					&& (vars->map[(int)vars->rays[i].rx - 1 + ((int)vars->rays[i].ry - 1) * vars->size.x] == '1'
					|| vars->map[(int)vars->rays[i].rx - 1 + ((int)vars->rays[i].ry - 1) * vars->size.x] == 'C'))
					ao = 1.0 - (vars->rays[i].rx - (int)vars->rays[i].rx) * 2.0;
				else if (vars->rays[i].rx - (int)vars->rays[i].rx > .5 && ((int)vars->rays[i].rx + 1) >= 0 && ((int)vars->rays[i].rx + 1) < vars->size.x
					&& ((int)vars->rays[i].ry - 1) >= 0 && ((int)vars->rays[i].ry - 1) < vars->size.y
					&& (vars->map[(int)vars->rays[i].rx + 1 + ((int)vars->rays[i].ry - 1) * vars->size.x] == '1'
					|| vars->map[(int)vars->rays[i].rx + 1 + ((int)vars->rays[i].ry - 1) * vars->size.x] == 'C'))
					ao = (vars->rays[i].rx - (int)vars->rays[i].rx) * 2.0 - 1.0;
				line_texture(vars, i, (1.0 - (vars->rays[i].rx - (int)vars->rays[i].rx)) * (get_texture(vars, "so", 0)->size.x + .0), get_texture(vars, "so", 0), vars->rays[i].dist, ao);
				//sud
			}
		}
		else
		{
			// vars->rays[i] = dist(vars->player.pos.x, vars->player.pos.y, disH.x, disH.y, vars->rays[i].ra2);
			//HIT HORIZONTAL
			if (vars->rays[i].ra2 > M_PI_2 && vars->rays[i].ra2 < M_PI_2 + M_PI)
			{
				// if (i == vars->win_size.x / 2)
				// 	printf("hit %d %d %.2f %.2f %c\n", (int)vars->rays[i].rx, (int)vars->rays[i].ry, vars->rays[i].rx - (int)vars->rays[i].rx, vars->rays[i].ry - (int)vars->rays[i].ry, 'W');
				if (vars->rays[i].ry - (int)vars->rays[i].ry < .5 && ((int)vars->rays[i].rx + 1) >= 0 && ((int)vars->rays[i].rx + 1) < vars->size.x
					&& ((int)vars->rays[i].ry - 1) >= 0 && ((int)vars->rays[i].ry - 1) < vars->size.y
					&& (vars->map[(int)vars->rays[i].rx + 1 + ((int)vars->rays[i].ry - 1) * vars->size.x] == '1'
					|| vars->map[(int)vars->rays[i].rx + 1 + ((int)vars->rays[i].ry - 1) * vars->size.x] == 'C'))
					ao = 1.0 - (vars->rays[i].ry - (int)vars->rays[i].ry) * 2.0;
				else if (vars->rays[i].ry - (int)vars->rays[i].ry > .5 && ((int)vars->rays[i].rx + 1) >= 0 && ((int)vars->rays[i].rx + 1) < vars->size.x
					&& ((int)vars->rays[i].ry + 1) >= 0 && ((int)vars->rays[i].ry + 1) < vars->size.y
					&& (vars->map[(int)vars->rays[i].rx + 1 + ((int)vars->rays[i].ry + 1) * vars->size.x] == '1'
					|| vars->map[(int)vars->rays[i].rx + 1 + ((int)vars->rays[i].ry + 1) * vars->size.x] == 'C'))
					ao = (vars->rays[i].ry - (int)vars->rays[i].ry) * 2.0 - 1.0;
				line_texture(vars, i, (1.0 - (vars->rays[i].ry - (int)vars->rays[i].ry)) * (get_texture(vars, "we", 0)->size.x + .0), get_texture(vars, "we", 0), vars->rays[i].dist, ao);
				//ouest
			}
			else
			{
				// if (i == vars->win_size.x / 2)
				// 	printf("hit %d %d %.2f %.2f %c\n", (int)vars->rays[i].rx, (int)vars->rays[i].ry, vars->rays[i].rx - (int)vars->rays[i].rx, vars->rays[i].ry - (int)vars->rays[i].ry, 'E');
				if (vars->rays[i].ry - (int)vars->rays[i].ry < .5 && ((int)vars->rays[i].rx - 1) >= 0 && ((int)vars->rays[i].rx - 1) < vars->size.x
					&& ((int)vars->rays[i].ry - 1) >= 0 && ((int)vars->rays[i].ry - 1) < vars->size.y
					&& (vars->map[(int)vars->rays[i].rx - 1 + ((int)vars->rays[i].ry - 1) * vars->size.x] == '1'
					|| vars->map[(int)vars->rays[i].rx - 1 + ((int)vars->rays[i].ry - 1) * vars->size.x] == 'C'))
					ao = 1.0 - (vars->rays[i].ry - (int)vars->rays[i].ry) * 2.0;
				else if (vars->rays[i].ry - (int)vars->rays[i].ry > .5 && ((int)vars->rays[i].rx - 1) >= 0 && ((int)vars->rays[i].rx - 1) < vars->size.x
					&& ((int)vars->rays[i].ry + 1) >= 0 && ((int)vars->rays[i].ry + 1) < vars->size.y
					&& (vars->map[(int)vars->rays[i].rx - 1 + ((int)vars->rays[i].ry + 1) * vars->size.x] == '1'
					|| vars->map[(int)vars->rays[i].rx - 1 + ((int)vars->rays[i].ry + 1) * vars->size.x] == 'C'))
					ao = (vars->rays[i].ry - (int)vars->rays[i].ry) * 2.0 - 1.0;
				line_texture(vars, i, (vars->rays[i].ry - (int)vars->rays[i].ry) * (get_texture(vars, "ea", 0)->size.x + .0), get_texture(vars, "ea", 0), vars->rays[i].dist, ao);
				//est
			}
		}
	}
}
