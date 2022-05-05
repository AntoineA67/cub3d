/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:54:13 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/05 13:35:06 by qroussea         ###   ########lyon.fr   */
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
			gen_coord( size + vars->player.pos.x, size+ vars->player.pos.y , 0, gen_color(255, 0, 100, 0)),
			gen_coord( (size + vars->player.pos.x) + vars->player.delta.x * 10.0,
				 (size + vars->player.pos.y) + vars->player.delta.y * 10.0, 0, gen_color(255, 0, 100, 0)));
	}
	else if (vars->settings.map_type == 2)
	{
		size = 64;
		draw_square_center(vars, gen_coord( size * (vars->player.pos.x + 1),
			size * (vars->player.pos.y + 1), size / 2.0, gen_color(255, 0, 100, 0)));
		plot_line(vars,
			gen_coord( size + vars->player.pos.x, size+ vars->player.pos.y , 0, gen_color(255, 0, 100, 0)),
			gen_coord( (size + vars->player.pos.x) + vars->player.delta.x * 10.0,
				 (size + vars->player.pos.y) + vars->player.delta.y * 10.0, 0, gen_color(255, 0, 100, 0)));
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

void	project_rays(t_vars *vars, double render_ratio)
{
	int			i;
	int			dof;
	int			mx;
	int			my;
	int			mp;
	int			size;
	int			shift;
	double		ra;
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
	t_vector2	disV;
	t_vector2	disH;

	(void)render_ratio;
	shift = 0;
	size = (int)vars->min_map_mult;
	while (size != 1)
	{
		size /= 2;
		shift++;
	}
	size = (int)vars->min_map_mult;
	i = -1;
	ra = fmod(vars->player.rot - M_PI_4 + (M_PI * 2) , M_PI * 2);
	start = ra;
	end = fmod(vars->player.rot + M_PI_4 + (M_PI * 2) , M_PI * 2);
	if (ra > end)
		end += (M_PI * 2);
	while (ra < end)
	{
		i++;
		dof = 0;
		ra2 =  fmod(ra , M_PI * 2);
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
			if (mp < vars->size.x * vars->size.y && mp >= 0 && (vars->map[mp] == '1' || vars->map[mp] == 'C'))
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
			if (mp < vars->size.x * vars->size.y && mp >= 0 && (vars->map[mp] == '1' || vars->map[mp] == 'C'))
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
		if (min_dist < 1.0)
			min_dist = 1.0;
		int	wall_height = vars->win_size.y / 2 / min_dist;
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
				line_texture(vars, i, (rx - (int)rx) * (vars->textures.img_so.size.x + .0),
					wall_height, &vars->textures.img_so, (int)min_dist * 10);
				//sud
			}
			else
			{
				color = gen_color(0, 255, 0, 0);
				line_texture(vars, i, (rx - (int)rx) * (vars->textures.img_no.size.x + .0),
					wall_height, &vars->textures.img_no, (int)min_dist * 10);
				//nord
			}
		}
		else
		{
			//HIT HORIZONTAL
			if (ra2 > M_PI_2 && ra2 < M_PI_2 + M_PI)
			{
				color = gen_color(0, 0, 255, 0);
				line_texture(vars, i, (ry - (int)ry) * (vars->textures.img_ea.size.x + .0),
					wall_height, &vars->textures.img_ea, (int)min_dist * 10);
				//est
			}
			else
			{
				color = gen_color(255, 255, 0, 0);
				line_texture(vars, i, (ry - (int)ry) * (vars->textures.img_we.size.x + .0),
					wall_height, &vars->textures.img_we, (int)min_dist * 10);
				//ouest
			}
		}
		// if (ra2 == fmod(vars->player.rot - M_PI_4 + (M_PI * 2) , M_PI * 2))
		if (i == vars->win_size.x / 2)
		{
			// printf("%.2f %.2f	%.2f %.2f	%d %d	%.2f\n", vars->player.pos.x, vars->player.pos.y, rx, ry,
				// (int)rx, (int)ry, min_dist);
			// plot_line(vars,
			// 		gen_coord(vars->player.pos.x + size, size + vars->player.pos.y, 0, gen_color(10, 10, 10, 200)),
			// 		gen_coord(rx + size, size + ry, 0, gen_color(10, 10, 10, 200)));

		}
		//plot_line(vars,
			//	gen_coord(vars->player.pos.x + size, size + vars->player.pos.y, 0, gen_color(10, 10, 10, 200)),
			//	gen_coord(rx + size, size + ry, 0, gen_color(10, 10, 10, 200)));

		//MERGE
		// min_dist = dist(vars->player.pos.x, vars->player.pos.y, rx, ry, ra2);
		// double ca = vars->player.rot - ra2;
		// if (ca < 0)
		// 	ca += M_PI * 2;
		// if (ca > M_PI * 2)
		// 	ca -= M_PI * 2;
		// min_dist *= cos(ca);


		// while (++i % 10 != 9)
		// {
		// 	plot_line(vars,
		// 		gen_coord(i, 540 - (int)(10000 / min_dist), 0),
		// 		gen_coord(i, 540 + (int)(10000 / min_dist), 0));
		// }
		// printf("%.2f\n", ra2);
		// plot_line(vars,
		// 		gen_coord(i, 540 - (int)(10000 / (min_dist * (render_ratio / vars->min_map_mult))), 0, color),
		// 		gen_coord(i, 540 + (int)(10000 / (min_dist * (render_ratio / vars->min_map_mult))), 0, gen_color(0, 0, 0, 0)));
		// printf("%.2f %d\n", min_dist, (int)(10000 / min_dist));
		ra += M_PI_2 / vars->win_size.x;
	}
	i = -1;
	//start = fmod(start , M_PI * 2);
	//end = fmod(end , M_PI * 2);
	//printf("%d\n", vars->mult_n_players);
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
				printf("player%d:%f|%f|%f\\%f\n",i,start,angle,end, angle + (M_PI * 2.0));
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

void	render(t_vars *vars)
{
	// t_data	*img;

	// img = vars->img;
	// vars->img = vars->img2;
	int	x;
	int	y;

	mlx_mouse_get_pos(vars->win, &x, &y);
	// if (!vars->ui)
	// {
	// 	// printf("MOUSE %d %d\n", x, y);
	// 	if (x > vars->win_size.x / 2)
	// 	{
	// 		rotate_player(vars, 5);
	// 		mlx_mouse_move(vars->win, vars->win_size.x / 2, 0);
	// 	}
	// 	else if (x < vars->win_size.x / 2)
	// 	{
	// 		rotate_player(vars, -5);
	// 		mlx_mouse_move(vars->win, vars->win_size.x / 2, 0);
	// 	}
	// }
	check_inputs(vars);
	if (vars->mult_fd)
		serv_process(vars);
	ft_int_memset(vars->img->addr, to_rgb(vars->textures.c, 0),
		vars->img->line_length * vars->win_size.y / 8);
	ft_int_memset(vars->img->addr + vars->img->line_length * vars->win_size.y / 2
		, to_rgb(vars->textures.f, 0), vars->img->line_length * vars->win_size.y / 8);
	project_rays(vars, 64.0);
	draw_2d_map(vars, vars->min_map_mult);
	show_player(vars, vars->min_map_mult);
	if (vars->mult_fd)
		draw_multi(vars, vars->min_map_mult);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	// vars->img = img;
}
