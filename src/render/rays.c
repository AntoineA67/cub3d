/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:00:14 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/08 12:31:23 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	test_rays(t_vars *vars)
NOPROF
{
	int			x;
	double		camera_x;
	t_vector2	ray_dir;
	t_vector2	plane;
	t_vector2	side_dist;
	t_vector2	delta_dist;
	double		perp_wall_dist;
	t_coord		step;
	int			hit;
	int			side;
	t_coord		map;

	
	plane.x = 0.0;
	plane.y = 0.50;
	x = -1;
	while (++x < vars->win_size.x)
	{
		camera_x = 2 * x / (vars->win_size.x * 1.0) - 1;
		ray_dir.x = vars->player.delta.x + plane.x * camera_x;
		ray_dir.y = vars->player.delta.y + plane.y * camera_x;

		if (x == vars->win_size.x / 2)
			printf("RAY DIR %.2f %.2f\n", ray_dir.x, ray_dir.y);
		map.x = (int)vars->player.pos.x;
		map.y = (int)vars->player.pos.y;

		if (ray_dir.x == 0)
			delta_dist.x = 1e30;
		else
			delta_dist.x = sqrt(1 + (ray_dir.y * ray_dir.y) / (ray_dir.x * ray_dir.x));
		if (ray_dir.y == 0)
			delta_dist.y = 1e30;
		else
			delta_dist.y = sqrt(1 + (ray_dir.x * ray_dir.x) / (ray_dir.y * ray_dir.y));
		hit = 0;

		if (ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (vars->player.pos.x - map.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (map.x + 1.0 - vars->player.pos.x) * delta_dist.x;
		}
		if (ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (vars->player.pos.y - map.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (map.y + 1.0 - vars->player.pos.y) * delta_dist.y;
		}
		while (hit == 0)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step.y;
				side = 1;
			}
			if (vars->map[map.x + map.y * vars->size.x] == '1')
			{
				hit = 1;
				if (x == vars->win_size.x / 2)
					printf("%d %d\n", map.x, map.y);
			}
		}
		if (x == vars->win_size.x / 2)
			printf("%.2f %.2f\n", side_dist.x, delta_dist.x);
		if (side == 0)
			perp_wall_dist = side_dist.x - delta_dist.x;
		else
			perp_wall_dist = side_dist.y - delta_dist.y;
		int h = vars->win_size.y;
		int line_height = (int)(h / perp_wall_dist);
		int draw_start = -line_height / 2 + h / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + h / 2;
		if (draw_end >= h)
			draw_start = h - 1;
		int color;
		color = 0xffffff;
		if (side == 1)
			color = 0x808080;
		if (x == vars->win_size.x / 2)
			printf("%.2f %.2f line_height %d\n", vars->player.delta.x, vars->player.delta.y, line_height);
		while (draw_start < draw_end)
		{
			pixel_put(vars->img, x, draw_start, color);
			draw_start++;
		}
		
		// 	plot_line(vars,
		// 		gen_coord(x, draw_start, 0, gen_color(100, 100, 100, 0)),
		// 		gen_coord(x, draw_end, 0, gen_color(0, 0, 0, 0)));
		// plot_line(vars,
		// 	gen_coord(x, draw_start, 0, gen_color(255, 200, 200, 0)),
		// 	gen_coord(x, draw_end, 0, gen_color(0, 0, 0, 0)));
		// double wall_x;
		// if (side == 0)
		// 	wall_x = vars->player.pos.y + perp_wall_dist * ray_dir.y;
		// else
		// 	wall_x = vars->player.pos.x + perp_wall_dist * ray_dir.x;
		// wall_x += floor(wall_x);
		// int tex_x = (int)(wall_x * )
	}
	
}

void	calc_ray(t_vars *vars, t_ray *r)
{
	int			dof;
	int			mx;
	int			my;
	int			mp;
	// double		ca; 
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
		ry = (int)r->start_pos.y - .00001;
		rx = (r->start_pos.y - ry) * aTan + r->start_pos.x;
		yo = -1.0;
		xo = 1.0 * aTan;
	}
	if (r->ra2 < M_PI && r->ra2 != 0) //looking up
	{
		ry = (int)r->start_pos.y + 1.0;
		rx = (r->start_pos.y - ry) * aTan + r->start_pos.x;
		yo = 1.0;
		xo = -1.0 * aTan;
	}
	if (r->ra2 == 0.0 || r->ra2 == M_PI)//looking straight left or right
	{
		rx = r->start_pos.x;
		ry = r->start_pos.y;
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
		rx = (int)r->start_pos.x - .00001;
		ry = (r->start_pos.x - rx) * nTan + r->start_pos.y;
		xo = -1.0;
		yo = 1.0 * nTan;
	}
	if (r->ra2 > M_PI_2 * 3.0 || r->ra2 < M_PI_2) //looking right
	{
		rx = (int)r->start_pos.x + 1.0;
		ry = (r->start_pos.x - rx) * nTan + r->start_pos.y;
		xo = 1.0;
		yo = -1.0 * nTan;
	}
	if (r->ra2 == M_PI_2 || r->ra2 == M_PI_2 * 3.0)//looking straight left or right
	{
		rx = r->start_pos.x;
		ry = r->start_pos.y;
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
	if (dist(r->start_pos.x, r->start_pos.y, disV.x, disV.y, r->ra2) <
		dist(r->start_pos.x, r->start_pos.y, disH.x, disH.y, r->ra2))
	{
		//HIT VERTICAL
		rx = disV.x;
		ry = disV.y;
		r->side = 0;
	}
	min_dist = dist(r->start_pos.x, r->start_pos.y, rx, ry, r->ra2);
	r->dist = min_dist;
	r->ry = ry;
	r->rx = rx;
}


void	project_rays(t_vars *vars)
{
	int			i;
	// int			size;
	double		ao;
	double		ca;
	// double		tx;

	i = -1;
	vars->start = fmod(vars->player.rot.x - M_PI_4 + (M_2PI) , M_2PI);
	vars->end = fmod(vars->player.rot.x + M_PI_4 + (M_2PI) , M_2PI);
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
	i = -1;
	while (++i < vars->win_size.x)
	{
		ao = 0.0;
		if (vars->rays[i].side == 0)
		{
			// vars->rays[i] = dist(vars->player.pos.x, vars->player.pos.y, disV.x, disV.y, ra2);
			if (vars->rays[i].ra2 > M_PI)
			{
				vars->ao = 0;
				// if (vars->rays[i].rx - (int)vars->rays[i].rx < .5 && ((int)vars->rays[i].rx - 1) >= 0 && ((int)vars->rays[i].rx - 1) < vars->size.x
				// 	&& ((int)vars->rays[i].ry + 1) >= 0 && ((int)vars->rays[i].ry + 1) < vars->size.y
				// 	&& (vars->map[(int)vars->rays[i].rx - 1 + ((int)vars->rays[i].ry + 1) * vars->size.x] == '1'
				// 	|| vars->map[(int)vars->rays[i].rx - 1 + ((int)vars->rays[i].ry + 1) * vars->size.x] == 'C'))
				// 	ao = 1.0 - (vars->rays[i].rx - (int)vars->rays[i].rx) * 2.0;
				// else if (vars->rays[i].rx - (int)vars->rays[i].rx > .5 && ((int)vars->rays[i].rx + 1) >= 0 && ((int)vars->rays[i].rx + 1) < vars->size.x
				// 	&& ((int)vars->rays[i].ry + 1) >= 0 && ((int)vars->rays[i].ry + 1) < vars->size.y
				// 	&& (vars->map[(int)vars->rays[i].rx + 1 + ((int)vars->rays[i].ry + 1) * vars->size.x] == '1'
				// 	|| vars->map[(int)vars->rays[i].rx + 1 + ((int)vars->rays[i].ry + 1) * vars->size.x] == 'C'))
				// 	ao = (vars->rays[i].rx - (int)vars->rays[i].rx) * 2.0 - 1.0;
				line_texture(vars, i, (vars->rays[i].rx - (int)vars->rays[i].rx) * (get_animtexture(vars, "no", 0.2)->size.x + .0), get_animtexture(vars, "no", 0.2), vars->rays[i].dist, ao);
				//nord
			}
			else
			{
				vars->ao = 0;
				// if (vars->rays[i].rx - (int)vars->rays[i].rx < .5 && ((int)vars->rays[i].rx - 1) >= 0 && ((int)vars->rays[i].rx - 1) < vars->size.x
				// 	&& ((int)vars->rays[i].ry - 1) >= 0 && ((int)vars->rays[i].ry - 1) < vars->size.y
				// 	&& (vars->map[(int)vars->rays[i].rx - 1 + ((int)vars->rays[i].ry - 1) * vars->size.x] == '1'
				// 	|| vars->map[(int)vars->rays[i].rx - 1 + ((int)vars->rays[i].ry - 1) * vars->size.x] == 'C'))
				// 	ao = 1.0 - (vars->rays[i].rx - (int)vars->rays[i].rx) * 2.0;
				// else if (vars->rays[i].rx - (int)vars->rays[i].rx > .5 && ((int)vars->rays[i].rx + 1) >= 0 && ((int)vars->rays[i].rx + 1) < vars->size.x
				// 	&& ((int)vars->rays[i].ry - 1) >= 0 && ((int)vars->rays[i].ry - 1) < vars->size.y
				// 	&& (vars->map[(int)vars->rays[i].rx + 1 + ((int)vars->rays[i].ry - 1) * vars->size.x] == '1'
				// 	|| vars->map[(int)vars->rays[i].rx + 1 + ((int)vars->rays[i].ry - 1) * vars->size.x] == 'C'))
				// 	ao = (vars->rays[i].rx - (int)vars->rays[i].rx) * 2.0 - 1.0;
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
