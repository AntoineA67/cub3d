/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:54:13 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/06 13:40:52 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	show_player(t_vars *vars, double size)
{
	size = 16.0;
	if (vars->settings.map_type == 1)
	{
		draw_square_center(vars, gen_coord( size * (vars->player.pos.x + 1),
			size * (vars->player.pos.y + 1), size / 2.0, gen_color(255, 0, 100, 0)));
		plot_line(vars,
			gen_coord( size * (vars->player.pos.x + 1), size* (vars->player.pos.y + 1), 0, gen_color(255, 0, 100, 0)),
			gen_coord( (size * (vars->player.pos.x +1)) + vars->player.delta.x * 10.0,
				 (size * (vars->player.pos.y + 1)) + vars->player.delta.y * 10.0, 0, gen_color(255, 0, 100, 0)));
	}
	else if (vars->settings.map_type == 2)
	{
		size = 64;
		draw_square_center(vars, gen_coord( size * (vars->player.pos.x + 1),
			size * (vars->player.pos.y + 1), size / 2.0, gen_color(255, 0, 100, 0)));
		plot_line(vars,
			gen_coord( size * (vars->player.pos.x + 1), size* (vars->player.pos.y + 1) , 0, gen_color(255, 0, 100, 0)),
			gen_coord( (size * (vars->player.pos.x + 1)) + vars->player.delta.x * 10.0,
				 (size * (vars->player.pos.y + 1)) + vars->player.delta.y * 10.0, 0, gen_color(255, 0, 100, 0)));
	}
	else
	{
		draw_square_center(vars, gen_coord( size * 3.5,
			size * 3.5, size / 2.0, gen_color(255, 0, 100, 0)));
		plot_line(vars,
			gen_coord( size* 3.5, size* 3.5 , 0, gen_color(255, 0, 100, 0)),
			gen_coord( (size * 3.5) + vars->player.delta.x * 10.0,
				 (size * 3.5) + vars->player.delta.y * 10.0, 0, gen_color(255, 0, 100, 0)));
	}
}

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
	double		start;
	double		end;
	double		min_dist;
	double		tx;
	double		rotmpi;
	int			mapsizei;
	t_vector2	disV;
	t_vector2	disH;

	(void)render_ratio;
	size = (int)vars->min_map_mult;
	i = -1;
	start = fmod(vars->player.rot - M_PI_4 + (M_PI * 2) , M_PI * 2);
	end = fmod(vars->player.rot + M_PI_4 + (M_PI * 2) , M_PI * 2);
	if (start > end)
		end += (M_PI * 2);
	tx = (2.0 / vars->win_size.x);
	rotmpi = vars->player.rot + (M_PI * 2.0);
	mapsizei = vars->size.x * vars->size.y;
	while (i < vars->win_size.x)
	{
		i++;
		dof = 0;
		if (i == vars->win_size.x / 2)
			ra2 = vars->player.rot;
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
		ca = vars->player.rot - ra2;
		if (ca < 0)
			ca += M_PI * 2;
		if (ca > M_PI * 2)
			ca -= M_PI * 2;
		min_dist *= cos(ca);
		int	wall_height = vars->win_size.y / 2 / min_dist;
		//int	wall_height = 1000 / min_dist;
		// if (i == vars->win_size.x / 2)
		// 	printf("height %d min_dist %.3f\n", wall_height, min_dist);
		// printf("MIN DIST %.2f %.2f\n", min_dist, min_dist * cos(ca));
		// printf("OUI %d	%.3f	%d\n", vars->textures.img_no.size.x, (rx - (int)rx), vars->textures.img_no.size.x);
		(void)color;
		if (dist(vars->player.pos.x, vars->player.pos.y, disV.x, disV.y, ra2) <
			dist(vars->player.pos.x, vars->player.pos.y, disH.x, disH.y, ra2))
		{
			if (ra2 > M_PI)
			{
				color = gen_color(255, 0, 0, 0);
				line_texture(vars, i, (rx - (int)rx) * (get_texture(vars, "so", 0)->size.x + .0), get_texture(vars, "so", 0), min_dist);
				//sud
			}
			else
			{
				color = gen_color(0, 255, 0, 0);
				line_texture(vars, i, (rx - (int)rx) * (get_texture(vars, "no", 0)->size.x + .0), get_texture(vars, "no", 0), min_dist);
				//nord
			}
		}
		else
		{
			//HIT HORIZONTAL
			if (ra2 > M_PI_2 && ra2 < M_PI_2 + M_PI)
			{
				color = gen_color(0, 0, 255, 0);
				line_texture(vars, i, (ry - (int)ry) * (get_texture(vars, "ea", 0)->size.x + .0), get_texture(vars, "ea", 0), min_dist);
				//est
			}
			else
			{
				color = gen_color(255, 255, 0, 0);
				line_texture(vars, i, (ry - (int)ry) * (get_texture(vars, "we", 0)->size.x + .0), get_texture(vars, "we", 0), min_dist);
				//ouest
			}
		}
	}
	i = -1;
	while (++i < vars->mult_n_players && i < MAX_CLIENT)
	{
		if (vars->mult_id != i)
		{
			if (vars->mult_positions[i].y > 0.0 && vars->mult_positions[i].x > 0.0)
			{
				double angle = atan2((vars->player.pos.y - vars->mult_positions[i].y), (vars->player.pos.x - vars->mult_positions[i].x));
				if (angle < 0)
					angle = M_PI * 2 + angle;
				angle =  angle + M_PI;
				angle = fmod(angle, M_PI * 2);
				// printf("player%d:%f|%f|%f\\%f\n",i,start,angle,end, angle + (M_PI * 2.0));
				if (angle > start && angle < end )
				{
					double dangle = end - angle;
					draw_square_center(vars, gen_coord(vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2), vars->win_size.y / 2, (1 / dist(vars->player.pos.x, vars->player.pos.y, vars->mult_positions[i].x, vars->mult_positions[i].y, angle)) *100 , gen_color(100,100,100,0)));
				}
				else if (( angle + (M_PI * 2.0)) > start && (angle + (M_PI * 2.0)) < end)
				{
					double dangle = end - ( angle + (M_PI * 2.0));
					draw_square_center(vars, gen_coord(vars->win_size.x - ((dangle * vars->win_size.x) / M_PI_2), vars->win_size.y / 2, (1 / dist(vars->player.pos.x, vars->player.pos.y, vars->mult_positions[i].x, vars->mult_positions[i].y, angle)) *100 , gen_color(100,100,100,0)));	
				}
			}
		}
	}
	//plot_line(vars,
		//	gen_coord(vars->player.pos.x + size, size + vars->player.pos.y, 0, gen_color(255, 0, 100, 0)),
		//	gen_coord(rx + size, size + ry, 0, gen_color(255, 0, 100, 0)));
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

void	draw_multi(t_vars *vars, int size)
{
	int	i;

	i = -1;
	while (++i < vars->mult_n_players && i < MAX_CLIENT)
	{
		if (vars->mult_positions[i].x > 0 && vars->mult_positions[i].y > 0)
			draw_square_center(vars,
				gen_coord(vars->mult_positions[i].x * size + size, vars->mult_positions[i].y * size + size, size / 2,
				gen_color(255, 255, 255, 0)));
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
	ft_int_memset(vars->img->addr, to_rgb(vars->textures.c, 0),
		vars->img->line_length * vars->win_size.y / 8);
	ft_int_memset(vars->img->addr + vars->img->line_length * vars->win_size.y / 2
		, to_rgb(vars->textures.f, 0), vars->img->line_length * vars->win_size.y / 8);
}

void	render(t_vars *vars)
{
	// t_data	*img;

	// img = vars->img;
	// vars->img = vars->img2;
	int	x;
	int	y;
	void *tmp;

	tmp = vars->img;
	vars->img = vars->img2;
	vars->img2 = tmp;
	mlx_mouse_get_pos(vars->win, &x, &y);
	if (!vars->ui)
	{
		// printf("MOUSE %d %d\n", x, y);
		if (x > vars->win_size.x / 2)
		{
			rotate_player(vars, 5);
			mlx_mouse_move(vars->win, vars->win_size.x / 2, 0);
		}
		else if (x < vars->win_size.x / 2)
		{
			rotate_player(vars, -5);
			mlx_mouse_move(vars->win, vars->win_size.x / 2, 0);
		}
	}
	check_inputs(vars);
	if (vars->mult_fd)
		serv_process(vars);
<<<<<<< HEAD
	ft_int_memset(vars->img->addr, to_rgb(vars->c, 0),
		vars->img->line_length * vars->win_size.y / 8);
	ft_int_memset(vars->img->addr + vars->img->line_length * vars->win_size.y / 2
		, to_rgb(vars->f, 0), vars->img->line_length * vars->win_size.y / 8);
=======
	shade_floor_ceil(vars);
>>>>>>> ae2c5cfdf71c89fb22f29dfe52eb7e7fa89249f7
	project_rays(vars, 64.0);
	//test_rays(vars);
	draw_2d_map(vars, vars->min_map_mult);
	show_player(vars, vars->min_map_mult);
	if (vars->mult_fd)
		draw_multi(vars, vars->min_map_mult);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	// vars->img = img;
}
