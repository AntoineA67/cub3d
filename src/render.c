/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:54:13 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/12 14:23:37 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

double	dist(double ax, double ay, double bx, double by, double angle)
{
	(void)angle;
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

// void	test_rays(t_vars *vars)
// {
// 	int			x;
// 	double		camera_x;
// 	t_vector2	ray_dir;
// 	t_vector2	plane;
// 	t_vector2	side_dist;
// 	t_vector2	delta_dist;
// 	double		perp_wall_dist;
// 	t_coord		step;
// 	int			hit;
// 	int			side;
// 	t_coord		map;

	
// 	plane.x = 0.0;
// 	plane.y = 0.50;
// 	x = -1;
// 	while (++x < vars->win_size.x)
// 	{
// 		camera_x = 2 * x / (vars->win_size.x * 1.0) - 1;
// 		ray_dir.x = vars->player.delta.x + plane.x * camera_x;
// 		ray_dir.y = vars->player.delta.y + plane.y * camera_x;

// 		if (x == vars->win_size.x / 2)
// 			printf("RAY DIR %.2f %.2f\n", ray_dir.x, ray_dir.y);
// 		map.x = (int)vars->player.pos.x;
// 		map.y = (int)vars->player.pos.y;

// 		if (ray_dir.x == 0)
// 			delta_dist.x = 1e30;
// 		else
// 			delta_dist.x = sqrt(1 + (ray_dir.y * ray_dir.y) / (ray_dir.x * ray_dir.x));
// 		if (ray_dir.y == 0)
// 			delta_dist.y = 1e30;
// 		else
// 			delta_dist.y = sqrt(1 + (ray_dir.x * ray_dir.x) / (ray_dir.y * ray_dir.y));
// 		hit = 0;

// 		if (ray_dir.x < 0)
// 		{
// 			step.x = -1;
// 			side_dist.x = (vars->player.pos.x - map.x) * delta_dist.x;
// 		}
// 		else
// 		{
// 			step.x = 1;
// 			side_dist.x = (map.x + 1.0 - vars->player.pos.x) * delta_dist.x;
// 		}
// 		if (ray_dir.y < 0)
// 		{
// 			step.y = -1;
// 			side_dist.y = (vars->player.pos.y - map.y) * delta_dist.y;
// 		}
// 		else
// 		{
// 			step.y = 1;
// 			side_dist.y = (map.y + 1.0 - vars->player.pos.y) * delta_dist.y;
// 		}
// 		while (hit == 0)
// 		{
// 			if (side_dist.x < side_dist.y)
// 			{
// 				side_dist.x += delta_dist.x;
// 				map.x += step.x;
// 				side = 0;
// 			}
// 			else
// 			{
// 				side_dist.y += delta_dist.y;
// 				map.y += step.y;
// 				side = 1;
// 			}
// 			if (vars->map[map.x + map.y * vars->size.x] == '1')
// 			{
// 				hit = 1;
// 				if (x == vars->win_size.x / 2)
// 					printf("%d %d\n", map.x, map.y);
// 			}
// 		}
// 		if (x == vars->win_size.x / 2)
// 			printf("%.2f %.2f\n", side_dist.x, delta_dist.x);
// 		if (side == 0)
// 			perp_wall_dist = side_dist.x - delta_dist.x;
// 		else
// 			perp_wall_dist = side_dist.y - delta_dist.y;
// 		int h = vars->win_size.y;
// 		int line_height = (int)(h / perp_wall_dist);
// 		int draw_start = -line_height / 2 + h / 2;
// 		if (draw_start < 0)
// 			draw_start = 0;
// 		int draw_end = line_height / 2 + h / 2;
// 		if (draw_end >= h)
// 			draw_start = h - 1;
// 		int color;
// 		color = 0xffffff;
// 		if (side == 1)
// 			color = 0x808080;
// 		if (x == vars->win_size.x / 2)
// 			printf("%.2f %.2f line_height %d\n", vars->player.delta.x, vars->player.delta.y, line_height);
// 		while (draw_start < draw_end)
// 		{
// 			pixel_put(vars->img, x, draw_start, color);
// 			draw_start++;
// 		}
		
// 		// 	plot_line(vars,
// 		// 		gen_coord(x, draw_start, 0, gen_color(100, 100, 100, 0)),
// 		// 		gen_coord(x, draw_end, 0, gen_color(0, 0, 0, 0)));
// 		// plot_line(vars,
// 		// 	gen_coord(x, draw_start, 0, gen_color(255, 200, 200, 0)),
// 		// 	gen_coord(x, draw_end, 0, gen_color(0, 0, 0, 0)));
// 		// double wall_x;
// 		// if (side == 0)
// 		// 	wall_x = vars->player.pos.y + perp_wall_dist * ray_dir.y;
// 		// else
// 		// 	wall_x = vars->player.pos.x + perp_wall_dist * ray_dir.x;
// 		// wall_x += floor(wall_x);
// 		// int tex_x = (int)(wall_x * )
// 	}
	
// }

void	draw_square_texture_center(t_vars *vars, t_coord p, t_data *img, double dist_b_players)
{
	int		dy;
	int		dx;
	int		square_size;
	double	ratio_x;
	double	ratio_y;
	double	img_x;
	double	img_y;

	if (!p.z)
		return ;
	square_size = p.z;
	img_y = 0;
	(void)dist_b_players;
	ratio_x = (img->size.x + .0) / (square_size + .0);
	ratio_y = (img->size.y + .0) / (square_size + .0);
	dy = p.y - p.z / 2;
	// printf("img_x: %d	img_y: %d\nsquare_size: %d\nratio_x: %.2f	ratio_y: %.2f\n", img->size.x, img->size.y, square_size, ratio_x, ratio_y);
	// draw_square_center(vars, p);
	while (++dy < p.y + p.z / 2)
	{
		dx = p.x - p.z / 2;
		img_x = 0;
		while (++dx < p.x + p.z / 2 && img_x < img->size.x && img_y >= 0 && img_x >= 0 && img_y < img->size.y && is_in_window(vars, dx, dy - vars->player.rot.y - vars->jump_height / dist_b_players))
		{
			//printf("img_x: %f	img_y: %f\n", img_x, img_y);
			//printf("%d\n", img->line_length);
			// if ((*(unsigned int *)(img->addr + ((int)((int)img_x * (img->bits_per_pixel / 8)) + (int)((int)img_y * img->line_length)))>>24) != 255)
				pixel_put(vars->img, dx, dy - vars->player.rot.y - vars->jump_height / dist_b_players,
					*(unsigned int *)(img->addr + ((int)((int)img_x * (img->bits_per_pixel / 8)) + (int)((int)img_y * img->line_length))));
			// else
				// printf("aaa\n");
			img_x += ratio_x;
		}
		img_y += ratio_y;
	}
}

void	project_rays(t_vars *vars, double render_ratio)
{
	int			i;
	int			dof;
	int			mx;
	int			my;
	int			mp;
	int			size;
	double		ra2;
	double		ca; 
	double		aTan;
	double		nTan;
	double		ry;
	double		rx;
	double		yo;
	double		xo;
	double		min_dist;
	double		tx;
	double		rotmpi;
	int			mapsizei;
	t_vector2	disV;
	t_vector2	disH;

	(void)render_ratio;
	size = ft_max(vars->size.x, vars->size.y);
	i = -1;
	vars->start = fmod(vars->player.rot.x - M_PI_4 + (M_PI * 2) , M_PI * 2);
	vars->end = fmod(vars->player.rot.x + M_PI_4 + (M_PI * 2) , M_PI * 2);
	if (vars->start > vars->end)
		vars->end += (M_PI * 2);
	tx = (2.0 / vars->win_size.x);
	rotmpi = vars->player.rot.x + (M_PI * 2.0);
	mapsizei = vars->size.x * vars->size.y;
	while (++i < vars->win_size.x)
	{
		dof = 0;
		if (i == vars->win_size.x / 2)
			ra2 = vars->player.rot.x;
		else
			ra2 = fmod(rotmpi - atan(1.0 - (tx * i)), M_PI * 2.0);
		aTan = -1.0/tan(ra2);
		if (ra2 > M_PI) //looking down
		{
			ry = (int)vars->player.pos.y - .00001;
			rx = (vars->player.pos.y - ry) * aTan + vars->player.pos.x;
			yo = -1.0;
			xo = 1.0 * aTan;
		}
		if (ra2 < M_PI && ra2 != 0) //looking up
		{
			ry = (int)vars->player.pos.y + 1.0;
			rx = (vars->player.pos.y - ry) * aTan + vars->player.pos.x;
			yo = 1.0;
			xo = -1.0 * aTan;
		}
		if (ra2 == 0.0 || ra2 == M_PI)//looking straight left or right
		{
			rx = vars->player.pos.x;
			ry = vars->player.pos.y;
			dof = size;
		}
		while (dof < size)
		{
			mx = (int)rx;
			my = (int)ry;
			mp = my * vars->size.x + mx;
			if (mp < mapsizei && mp >= 0 && (vars->map[mp] == '1' || vars->map[mp] == 'C'))
				dof = size;
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
		nTan = -tan(ra2);
		if (ra2 > M_PI_2 && ra2 < M_PI_2 * 3.0) //looking left
		{
			rx = (int)vars->player.pos.x - .00001;
			ry = (vars->player.pos.x - rx) * nTan + vars->player.pos.y;
			xo = -1.0;
			yo = 1.0 * nTan;
		}
		if (ra2 > M_PI_2 * 3.0 || ra2 < M_PI_2) //looking right
		{
			rx = (int)vars->player.pos.x + 1.0;
			ry = (vars->player.pos.x - rx) * nTan + vars->player.pos.y;
			xo = 1.0;
			yo = -1.0 * nTan;
		}
		if (ra2 == M_PI_2 || ra2 == M_PI_2 * 3.0)//looking stra2ight left or right
		{
			rx = vars->player.pos.x;
			ry = vars->player.pos.y;
			dof = size;
		}
		while (dof < size)
		{
			mx = (int)rx;
			my = (int)ry;
			mp = my * vars->size.x + mx;
			if (mp < mapsizei && mp >= 0 && (vars->map[mp] == '1' || vars->map[mp] == 'C'))
				dof = size;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		disH.x = rx;
		disH.y = ry;
		t_rgb	color;
		if (dist(vars->player.pos.x, vars->player.pos.y, disV.x, disV.y, ra2) <
			dist(vars->player.pos.x, vars->player.pos.y, disH.x, disH.y, ra2))
		{
			//HIT VERTICAL
			rx = disV.x;
			ry = disV.y;
		}
		min_dist = dist(vars->player.pos.x, vars->player.pos.y, rx, ry, ra2);
		ca = vars->player.rot.x - ra2;
		if (ca < 0)
			ca += M_PI * 2;
		if (ca > M_PI * 2)
			ca -= M_PI * 2;
		min_dist *= cos(ca);
		//int	wall_height = 1000 / min_dist;
		// printf("MIN DIST %.2f %.2f\n", min_dist, min_dist * cos(ca));
		// printf("OUI %d	%.3f	%d\n", vars->textures.img_no.size.x, (rx - (int)rx), vars->textures.img_no.size.x);
		(void)color;
		double	ao;
		ao = 0.0;
		if (dist(vars->player.pos.x, vars->player.pos.y, disV.x, disV.y, ra2) <
			dist(vars->player.pos.x, vars->player.pos.y, disH.x, disH.y, ra2))
		{
			vars->rays[i] = dist(vars->player.pos.x, vars->player.pos.y, disV.x, disV.y, ra2);
			if (ra2 > M_PI)
			{
				// if (i == vars->win_size.x / 2)
				// 	printf("hit %d %d %.2f %.2f %c\n", (int)rx, (int)ry, rx - (int)rx, ry - (int)ry, 'N');
				if (rx - (int)rx < .5 && ((int)rx - 1) >= 0 && ((int)rx - 1) < vars->size.x
					&& ((int)ry + 1) >= 0 && ((int)ry + 1) < vars->size.y
					&& (vars->map[(int)rx - 1 + ((int)ry + 1) * vars->size.x] == '1'
					|| vars->map[(int)rx - 1 + ((int)ry + 1) * vars->size.x] == 'C'))
					ao = 1.0 - (rx - (int)rx) * 2.0;
				else if (rx - (int)rx > .5 && ((int)rx + 1) >= 0 && ((int)rx + 1) < vars->size.x
					&& ((int)ry + 1) >= 0 && ((int)ry + 1) < vars->size.y
					&& (vars->map[(int)rx + 1 + ((int)ry + 1) * vars->size.x] == '1'
					|| vars->map[(int)rx + 1 + ((int)ry + 1) * vars->size.x] == 'C'))
					ao = (rx - (int)rx) * 2.0 - 1.0;
				// line_texture(vars, i, (rx - (int)rx) * (get_texture(vars, "no", 0)->size.x + .0), get_texture(vars, "no", 0), min_dist, ao);
				line_texture(vars, i, (rx - (int)rx) * (get_animtexture(vars, "player", 0.2)->size.x + .0), get_animtexture(vars, "player", 0.2), min_dist, ao);
				//nord
			}
			else
			{
				// if (i == vars->win_size.x / 2)
				// 	printf("hit %d %d %.2f %.2f %c\n", (int)rx, (int)ry, rx - (int)rx, ry - (int)ry, 'S');
				if (rx - (int)rx < .5 && ((int)rx - 1) >= 0 && ((int)rx - 1) < vars->size.x
					&& ((int)ry - 1) >= 0 && ((int)ry - 1) < vars->size.y
					&& (vars->map[(int)rx - 1 + ((int)ry - 1) * vars->size.x] == '1'
					|| vars->map[(int)rx - 1 + ((int)ry - 1) * vars->size.x] == 'C'))
					ao = 1.0 - (rx - (int)rx) * 2.0;
				else if (rx - (int)rx > .5 && ((int)rx + 1) >= 0 && ((int)rx + 1) < vars->size.x
					&& ((int)ry - 1) >= 0 && ((int)ry - 1) < vars->size.y
					&& (vars->map[(int)rx + 1 + ((int)ry - 1) * vars->size.x] == '1'
					|| vars->map[(int)rx + 1 + ((int)ry - 1) * vars->size.x] == 'C'))
					ao = (rx - (int)rx) * 2.0 - 1.0;
				line_texture(vars, i, (1.0 - (rx - (int)rx)) * (get_texture(vars, "so", 0)->size.x + .0), get_texture(vars, "so", 0), min_dist, ao);
				//sud
			}
		}
		else
		{
			vars->rays[i] = dist(vars->player.pos.x, vars->player.pos.y, disH.x, disH.y, ra2);
			//HIT HORIZONTAL
			if (ra2 > M_PI_2 && ra2 < M_PI_2 + M_PI)
			{
				// if (i == vars->win_size.x / 2)
				// 	printf("hit %d %d %.2f %.2f %c\n", (int)rx, (int)ry, rx - (int)rx, ry - (int)ry, 'W');
				if (ry - (int)ry < .5 && ((int)rx + 1) >= 0 && ((int)rx + 1) < vars->size.x
					&& ((int)ry - 1) >= 0 && ((int)ry - 1) < vars->size.y
					&& (vars->map[(int)rx + 1 + ((int)ry - 1) * vars->size.x] == '1'
					|| vars->map[(int)rx + 1 + ((int)ry - 1) * vars->size.x] == 'C'))
					ao = 1.0 - (ry - (int)ry) * 2.0;
				else if (ry - (int)ry > .5 && ((int)rx + 1) >= 0 && ((int)rx + 1) < vars->size.x
					&& ((int)ry + 1) >= 0 && ((int)ry + 1) < vars->size.y
					&& (vars->map[(int)rx + 1 + ((int)ry + 1) * vars->size.x] == '1'
					|| vars->map[(int)rx + 1 + ((int)ry + 1) * vars->size.x] == 'C'))
					ao = (ry - (int)ry) * 2.0 - 1.0;
				line_texture(vars, i, (1.0 - (ry - (int)ry)) * (get_texture(vars, "we", 0)->size.x + .0), get_texture(vars, "we", 0), min_dist, ao);
				//ouest
			}
			else
			{
				// if (i == vars->win_size.x / 2)
				// 	printf("hit %d %d %.2f %.2f %c\n", (int)rx, (int)ry, rx - (int)rx, ry - (int)ry, 'E');
				if (ry - (int)ry < .5 && ((int)rx - 1) >= 0 && ((int)rx - 1) < vars->size.x
					&& ((int)ry - 1) >= 0 && ((int)ry - 1) < vars->size.y
					&& (vars->map[(int)rx - 1 + ((int)ry - 1) * vars->size.x] == '1'
					|| vars->map[(int)rx - 1 + ((int)ry - 1) * vars->size.x] == 'C'))
					ao = 1.0 - (ry - (int)ry) * 2.0;
				else if (ry - (int)ry > .5 && ((int)rx - 1) >= 0 && ((int)rx - 1) < vars->size.x
					&& ((int)ry + 1) >= 0 && ((int)ry + 1) < vars->size.y
					&& (vars->map[(int)rx - 1 + ((int)ry + 1) * vars->size.x] == '1'
					|| vars->map[(int)rx - 1 + ((int)ry + 1) * vars->size.x] == 'C'))
					ao = (ry - (int)ry) * 2.0 - 1.0;
				line_texture(vars, i, (ry - (int)ry) * (get_texture(vars, "ea", 0)->size.x + .0), get_texture(vars, "ea", 0), min_dist, ao);
				//est
			}
		}
	}
}

void	draw_enemies(t_vars *vars)
{
	int		i;
	double	angle;
	double	dist_enemy;
	double	dangle;
	int		screen_x;

	i = -1;
	while (++i < vars->n_enemies)
	{
		if (vars->enemies[i].lives > 0)
		{
			angle = atan2((vars->player.pos.y - vars->enemies[i].pos.y), (vars->player.pos.x - vars->enemies[i].pos.x));
			if (angle < 0)
				angle = M_PI * 2 + angle;
			angle =  angle + M_PI;
			angle = fmod(angle, M_PI * 2);
			// printf("player%d:%f|%f|%f\\%f\n",i,vars->start,angle,vars->end, angle + (M_PI * 2.0));
			dist_enemy = dist(vars->player.pos.x, vars->player.pos.y, vars->enemies[i].pos.x, vars->enemies[i].pos.y, angle);
			if (angle > vars->start && angle < vars->end)
			{
				dangle = vars->end - angle;
				screen_x = vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2);
				if (screen_x < vars->win_size.x && screen_x > 0 && vars->rays[screen_x] > dist_enemy)
				{
					vars->enemies[i].pos.x += .08 - .16 * (vars->player.pos.x < vars->enemies[i].pos.x);
					vars->enemies[i].pos.y += .08 - .16 * (vars->player.pos.y < vars->enemies[i].pos.y);
					draw_square_texture_center(vars, gen_coord(screen_x, vars->win_size.y / 2, (1 / dist_enemy) * (vars->win_size.y / 2), gen_color(100,100,100,0)), get_texture(vars, "oui", 0), dist_enemy);
				}
				// draw_square_texture_center(vars, gen_coord(vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2), vars->win_size.y / 2, (1 / dist(vars->player.pos.x, vars->player.pos.y, vars->mult_positions[i].x, vars->mult_positions[i].y, angle)) * 200, gen_color(100,100,100,0)), get_animtexture(vars, "player", 0.2));
				// draw_square_center(vars, gen_coord(vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2), vars->win_size.y / 2, (1 / dist(vars->player.pos.x, vars->player.pos.y, vars->mult_positions[i].x, vars->mult_positions[i].y, angle)) *100 , gen_color(100,100,100,0)));
			}
			else if (( angle + (M_PI * 2.0)) > vars->start && (angle + (M_PI * 2.0)) < vars->end)
			{
				dangle = vars->end - (angle + (M_PI * 2.0));
				screen_x = vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2);
				if (screen_x < vars->win_size.x && screen_x > 0 && vars->rays[screen_x] > dist_enemy)
				{
					vars->enemies[i].pos.x += .08 - .16 * (vars->player.pos.x < vars->enemies[i].pos.x);
					vars->enemies[i].pos.y += .08 - .16 * (vars->player.pos.y < vars->enemies[i].pos.y);
					draw_square_texture_center(vars, gen_coord(screen_x, vars->win_size.y / 2, (1 / dist_enemy) * (vars->win_size.y / 2), gen_color(100,100,100,0)), get_texture(vars, "oui", 0), dist_enemy);	
				}
				// draw_square_center(vars, gen_coord(vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2), vars->win_size.y / 2, (1 / dist(vars->player.pos.x, vars->player.pos.y, vars->mult_positions[i].x, vars->mult_positions[i].y, angle)) *100 , gen_color(100,100,100,0)));	
			}
		}
	}
}

void	draw_other_players(t_vars *vars)
{
	int		i;
	double	angle;
	double	dist_players;
	double	dangle;
	int		screen_x;

	i = -1;
	while (++i < vars->mult_n_players && i < MAX_CLIENT)
	{
		if (vars->mult_id != i)
		{
			if (vars->mult_positions[i].y > 0.0 && vars->mult_positions[i].x > 0.0)
			{
				angle = atan2((vars->player.pos.y - vars->mult_positions[i].y), (vars->player.pos.x - vars->mult_positions[i].x));
				if (angle < 0)
					angle = M_PI * 2 + angle;
				angle =  angle + M_PI;
				angle = fmod(angle, M_PI * 2);
				// printf("player%d:%f|%f|%f\\%f\n",i,vars->start,angle,vars->end, angle + (M_PI * 2.0));
				dist_players = dist(vars->player.pos.x, vars->player.pos.y, vars->mult_positions[i].x, vars->mult_positions[i].y, angle);
				if (angle > vars->start && angle < vars->end)
				{
					dangle = vars->end - angle;
					screen_x = vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2);
					if (screen_x < vars->win_size.x && screen_x > 0 && vars->rays[screen_x] > dist_players)
						draw_square_texture_center(vars, gen_coord(screen_x, vars->win_size.y / 2, (1 / dist_players) * (vars->win_size.y / 2), gen_color(100,100,100,0)), get_texture(vars, "oui", 0), dist_players);
					// draw_square_texture_center(vars, gen_coord(vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2), vars->win_size.y / 2, (1 / dist(vars->player.pos.x, vars->player.pos.y, vars->mult_positions[i].x, vars->mult_positions[i].y, angle)) * 200, gen_color(100,100,100,0)), get_animtexture(vars, "player", 0.2));
					// draw_square_center(vars, gen_coord(vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2), vars->win_size.y / 2, (1 / dist(vars->player.pos.x, vars->player.pos.y, vars->mult_positions[i].x, vars->mult_positions[i].y, angle)) *100 , gen_color(100,100,100,0)));
				}
				else if (( angle + (M_PI * 2.0)) > vars->start && (angle + (M_PI * 2.0)) < vars->end)
				{
					dangle = vars->end - (angle + (M_PI * 2.0));
					screen_x = vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2);
					if (screen_x < vars->win_size.x && screen_x > 0 && vars->rays[screen_x] > dist_players)
						draw_square_texture_center(vars, gen_coord(screen_x, vars->win_size.y / 2, (1 / dist_players) * (vars->win_size.y / 2), gen_color(100,100,100,0)), get_texture(vars, "oui", 0), dist_players);	
					// draw_square_center(vars, gen_coord(vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2), vars->win_size.y / 2, (1 / dist(vars->player.pos.x, vars->player.pos.y, vars->mult_positions[i].x, vars->mult_positions[i].y, angle)) *100 , gen_color(100,100,100,0)));	
				}
			}
		}
	}
}

void	draw_square_center(t_vars *vars, t_coord p)
{
	int	dy;
	int	dx;

	dy = p.y - p.z / 2;
	while (++dy < p.y + p.z / 2)
	{
		dx = p.x - p.z / 2;
		while (++dx < p.x + p.z / 2)
			if (is_in_window(vars, dx, dy))
				pixel_put(vars->img, dx,
						dy, to_rgb(p.c, 0));
	}
}

void	draw_square(t_vars *vars, t_coord p)
{
	int	dy;
	int	dx;

	dy = p.y;
	while (++dy < p.y + p.z)
	{
		dx = p.x;
		while (++dx < p.x + p.z)
			if (is_in_window(vars, dx, dy))
				pixel_put(vars->img, dx,
						dy, to_rgb(p.c, 0));
	}
}

void	draw_2d_enemies(t_vars *vars, int size)
{
	int	i;

	i = -1;
	while (++i < vars->n_enemies)
	{
		if (vars->enemies[i].lives > 0)
		{
			draw_square_center(vars,
				gen_coord(vars->enemies[i].pos.x * size + size, vars->enemies[i].pos.y * size + size, size / 2,
				gen_color(0, 0, 255, 0)));
		}
	}
}

void	draw_multi(t_vars *vars, int size)
{
	int	i;

	i = -1;
	while (++i < vars->mult_n_players && i < MAX_CLIENT)
	{
		if (i != vars->mult_id && vars->mult_positions[i].x > 0 && vars->mult_positions[i].y > 0)
			draw_square_center(vars,
				gen_coord(vars->mult_positions[i].x * size + size, vars->mult_positions[i].y * size + size, size / 2,
				gen_color(255, 255, 255, 0)));
	}
}

void	draw_bullets(t_vars *vars, int size)
{
	int		i;
	double	angle;
	double	dist_bullet;
	double	dangle;
	int		screen_x;

	i = -1;
	while (++i < MAX_CLIENT)
	{
		if (vars->bullets[i].pos.x >= 0)
			draw_square_center(vars,
				gen_coord(vars->bullets[i].pos.x * size + size, vars->bullets[i].pos.y * size + size, size / 2,
				gen_color(0, 255, 0, 0)));
	}

	i = -1;
	while (++i < MAX_CLIENT)
	{
		if (vars->bullets[i].pos.x > 0.0)
		{
			angle = atan2((vars->player.pos.y - vars->bullets[i].pos.y), (vars->player.pos.x - vars->bullets[i].pos.x));
			if (angle < 0)
				angle = M_PI * 2 + angle;
			angle =  angle + M_PI;
			angle = fmod(angle, M_PI * 2);
			// printf("player%d:%f|%f|%f\\%f\n",i,vars->start,angle,vars->end, angle + (M_PI * 2.0));
			dist_bullet = dist(vars->player.pos.x, vars->player.pos.y, vars->bullets[i].pos.x, vars->bullets[i].pos.y, angle);
			if (angle > vars->start && angle < vars->end)
			{
				dangle = vars->end - angle;
				screen_x = vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2);
				if (screen_x < vars->win_size.x && screen_x > 0 && vars->rays[screen_x] > dist_bullet)
					// draw_square_center(vars, gen_coord(screen_x, vars->win_size.y / 2, (1 / dist_bullet) * (vars->win_size.y / 2) * .2, gen_color(100,100,100,0)));
					draw_square_texture_center(vars, gen_coord(screen_x, vars->win_size.y / 2, (1 / dist_bullet) * (vars->win_size.y / 2) * .2, gen_color(100,100,100,0)), get_texture(vars, "bullet", 0), dist_bullet);
			}
			else if (( angle + (M_PI * 2.0)) > vars->start && (angle + (M_PI * 2.0)) < vars->end)
			{
				dangle = vars->end - (angle + (M_PI * 2.0));
				screen_x = vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2);
				if (screen_x < vars->win_size.x && screen_x > 0 && vars->rays[screen_x] > dist_bullet)
					// draw_square_center(vars, gen_coord(screen_x, vars->win_size.y / 2, (1 / dist_bullet) * (vars->win_size.y / 2) * .2, gen_color(100,100,100,0)));	
					draw_square_texture_center(vars, gen_coord(screen_x, vars->win_size.y / 2, (1 / dist_bullet) * (vars->win_size.y / 2) * .2, gen_color(100,100,100,0)), get_texture(vars, "bullet", 0), dist_bullet);
			}
		}
	}
}

void	draw_2d_map(t_vars *vars, int size)
{
	int	x;
	int	y;
	int	pos;
	int x1;
	int y1;
	int k;

	y = -1;
	pos = -1;
	x1 = 0;
	y1 = 0;
	k = 0;
	size = 16;
	while (++y < vars->size.y)
	{
		x = -1;
		while (++x < vars->size.x && ++pos >= 0)
		{
			//printf("%c", vars->map[x + y * vars->size.x]);
		if (vars->settings.map_type == 1)
		{
			if (vars->map[pos] == '0')
				draw_square(vars, gen_coord(x * size + size, y * size + size, size, gen_color(100, 100, 100, 0)));
			else if (vars->map[pos] == '1')
				draw_square(vars, gen_coord(x * size + size, y * size + size, size, gen_color(200, 200, 200, 0)));
			else if (vars->map[pos] == 'O' || vars->map[pos] == 'C')
				draw_square(vars, gen_coord(x * size + size, y * size + size, size,
					gen_color(150, 20, 150, 0)));
			
		}
		else if (vars->settings.map_type == 2)
		{
			size = 64;
			if (vars->map[pos] == '0')
				draw_square(vars, gen_coord(x * size + size, y * size + size, size, gen_color(100, 100, 100, 0)));
			else if (vars->map[pos] == '1')
				draw_square(vars, gen_coord(x * size + size, y * size + size, size, gen_color(200, 200, 200, 0)));
			else if (vars->map[pos] == 'O' || vars->map[pos] == 'C')
				draw_square(vars, gen_coord(x * size + size, y * size + size, size,
					gen_color(150, 20, 150, 0)));
		}
		else if (y >= ((int)vars->player.pos.y - 2) && y <= ((int)vars->player.pos.y + 2)&&
			x >= ((int)vars->player.pos.x - 2) && x <= ((int)vars->player.pos.x + 2))
		{
			//k++;
			//if (k != 1)
			//{
			if (vars->map[pos] == '0')
				draw_square(vars, gen_coord((x1++ * size) + size, y1 * size + size, size, gen_color(100, 100, 100, 0)));
			else if (vars->map[pos] == '1')
				draw_square(vars, gen_coord((x1++ * size) + size, y1 * size + size, size, gen_color(200, 200, 200, 0)));
			else if (vars->map[pos] == 'O' || vars->map[pos] == 'C')
				draw_square(vars, gen_coord((x1++ * size) + size, y1 * size + size, size,
					gen_color(150, 20, 150, 0)));
			//}
			//else
			//	x++;
			if (x1 == 5)
			{
				x1 = 0;
				y1++;
			}
		}
	//	else
		//	draw_square(vars, gen_coord(x1 * size + size, y1 * size + size, size, vars->textures.c));
		}
	}
		//printf("\n");
}

void	shade_floor_ceil(t_vars *vars)
{
	// int	i;

	// i = -1;
	// while (++i < vars->win_size.y * 2)
	// {
	// 	//ft_int_memset(vars->img->addr + i * vars->win_size.x, to_rgb(vars->textures.c, 0), vars->win_size.x);
	// 	ft_int_memset(vars->img->addr + i * vars->win_size.x, add_shade(vars, to_rgb(vars->textures.c, 0), i / 10), vars->win_size.x);
	// }
	// while (i < vars->win_size.y * 4 - 1)
	// {
	// 	ft_int_memset(vars->img->addr + i * vars->win_size.x, add_shade(vars, to_rgb(vars->textures.f, 0), 255 / i), vars->win_size.x);
	// 	i++;
	// }
	double	ceiling;

	ceiling = 1.0 - (vars->player.rot.y + vars->win_size.y / 2) / vars->win_size.y;
	if (ceiling < 0.0)
		ceiling = 0.0;
	// printf("%.2f\n", vars->win_size.y - ceiling * vars->win_size.y);
	ft_int_memset(vars->img->addr,
		to_rgb(vars->f, 0), vars->win_size.y * vars->win_size.x);
	ft_int_memset(vars->img->addr, to_rgb(vars->c, 0),  vars->win_size.y * ceiling * vars->win_size.x);
	// ft_int_memset(vars->img->addr + (int)(ceiling * vars->win_size.y * vars->img->line_length),
	// 	to_rgb(vars->f, 0), (vars->win_size.y - ceiling * vars->win_size.y) * vars->win_size.x);
}

int	check_enemy_nearby(t_vars *vars, t_vector2 *bullet_pos)
{
	int		i;
	double	hitbox;

	i = -1;
	hitbox = .3;
	while (++i < vars->n_enemies)
	{
		if (vars->enemies[i].lives > 0)
		{
			// printf("%.2f %.2f	%.2f %.2f\n", bullet_pos->x, bullet_pos->y, vars->enemies[i].pos.x, vars->enemies[i].pos.y);
			if (bullet_pos->x > vars->enemies[i].pos.x - hitbox
				&& bullet_pos->x < vars->enemies[i].pos.x + hitbox
				&& bullet_pos->y > vars->enemies[i].pos.y - hitbox
				&& bullet_pos->y < vars->enemies[i].pos.y + hitbox)
			{
				vars->enemies[i].lives--;
				return (1);
			}
		}
	}
	return (0);
}

void	process_bullets(t_vars *vars)
{
	int			i;
	t_vector2	new_pos;
	int			hit;

	i = -1;
	while (++i < MAX_CLIENT)
	{
		if (vars->bullets[i].pos.x > 0)
		{
			hit = 0;
			new_pos.x = vars->bullets[i].pos.x + vars->bullets[i].delta.x * .5;
			new_pos.y = vars->bullets[i].pos.y + vars->bullets[i].delta.y * .5;
			if (vars->map[(int)new_pos.x + (int)vars->bullets[i].pos.y * vars->size.x] != 'C'
				&& vars->map[(int)new_pos.x + (int)vars->bullets[i].pos.y * vars->size.x] != '1')
				vars->bullets[i].pos.x = new_pos.x;
			else
				hit = 1;
			if (vars->map[(int)vars->bullets[i].pos.x + (int)new_pos.y * vars->size.x] != 'C'
				&& vars->map[(int)vars->bullets[i].pos.x + (int)new_pos.y * vars->size.x] != '1')
				vars->bullets[i].pos.y = new_pos.y;
			else
				hit = 1;
			if (check_enemy_nearby(vars, &vars->bullets[i].pos))
			{
				hit = 1;
				printf("HIT ENEMY\n");
			}
			if (hit)
				vars->bullets[i].pos.x = -1;
			// printf("%.2f %.2f	%.2f %.2f\n", vars->bullets[i].pos.x, vars->bullets[i].pos.y, vars->bullets[i].delta.x, vars->bullets[i].delta.y);
		}
	}
}

void	gen_bullet(t_vars *vars)
{
	vars->bullets[0].pos.x = vars->player.pos.x;
	vars->bullets[0].pos.y = vars->player.pos.y;
	vars->bullets[0].delta.x = cos(vars->player.rot.x);
	vars->bullets[0].delta.y = sin(vars->player.rot.x);
	printf("%.2f %.2f\n", vars->player.delta.x, vars->player.delta.y);
}

void	draw_hud(t_vars *vars)
{
	// Cursor
	draw_square_center(vars, gen_coord(vars->win_size.x / 2, vars->win_size.y / 2, 4, gen_color(255, 255, 255, 0)));
	draw_square_center(vars, gen_coord(vars->win_size.x / 2, vars->win_size.y / 2, 2, gen_color(0, 0, 0, 0)));

}

void	render(t_vars *vars)
{
	// t_data	*img;

	// img = vars->img;
	// vars->img = vars->img2;
	int		x;
	int		y;
	time_t	jump_time;

	//void *tmp;

//	tmp = vars->img;
//	vars->img = vars->img2;
	//vars->img2 = tmp;
	mlx_mouse_get_pos(vars->win, &x, &y);
	// printf("%.2f\n", vars->player.rot.y);
	if (!vars->ui)
	{
		// printf("MOUSE %d %d\n", x, y);
		if (x > vars->win_size.x / 2)
			rotate_player_x(vars, x - vars->win_size.x / 2);
		else if (x < vars->win_size.x / 2)
			rotate_player_x(vars, x - vars->win_size.x / 2);
		if (vars->player.rot.y + (y - vars->win_size.y / 2)
			* vars->settings.y_ratio_mouse_speed > -vars->win_size.y / 2
			&& vars->player.rot.y + (y - vars->win_size.y / 2) * vars->settings.y_ratio_mouse_speed < vars->win_size.y / 2)
			vars->player.rot.y += (y - vars->win_size.y / 2) * vars->settings.y_ratio_mouse_speed;
		mlx_mouse_move(vars->win, vars->win_size.x / 2,  vars->win_size.y / 2);
		// if (vars->player.rot.y + jump_height < vars->win_size.y && vars->player.rot.y + jump_height > 0)
		// 	vars->player.rot.y += 
	}
	jump_time = gettime(vars->n1) - vars->jump;
	if (jump_time < 1000)
		vars->jump_height = -(((-1.0 / 1000.0) * ((int)jump_time * (int)jump_time) + .0) + (int)jump_time) * 1.5;
	else
		vars->jump_height = 0.0;
	shade_floor_ceil(vars);
	project_rays(vars, 64.0);
	draw_other_players(vars);
	draw_enemies(vars);
	//test_rays(vars);
	draw_2d_map(vars, vars->min_map_mult);
	show_player(vars, vars->min_map_mult);
	process_bullets(vars);
	draw_bullets(vars, vars->min_map_mult);
	if (vars->mult_fd)
		draw_multi(vars, vars->min_map_mult);
	draw_2d_enemies(vars, vars->min_map_mult);
	draw_hud(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	// vars->img = img;
}
