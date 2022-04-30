/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:54:13 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/30 15:01:13 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	show_player(t_vars *vars, double size)
{
	draw_square_center(vars, gen_coord(vars->player.pos.x + size,
		size + vars->player.pos.y, size / 2.0, gen_color(255, 0, 100, 0)));
	// p1.x = ((int)vars->player.pos.x>>6) * size + x;
	// p1.y = ((int)vars->player.pos.y>>6) * size + y;
	// p2.x = (((int)vars->player.pos.x>>6) + vars->player.delta.x) * size + x;
	// p2.y = (((int)vars->player.pos.y>>6) + vars->player.delta.y) * size + y;
	plot_line(vars,
		gen_coord(vars->player.pos.x + size, size + vars->player.pos.y, 0, gen_color(255, 0, 100, 0)),
		gen_coord(vars->player.pos.x + size + vars->player.delta.x * 10.0,
			vars->player.pos.y + size + vars->player.delta.y * 10.0, 0, gen_color(255, 0, 100, 0)));
	// printf("%d %d	%d %d\n", p1.x, p1.y, p2.x, p2.y);
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
	double		aTan;
	double		nTan;
	double		ry;
	double		rx;
	double		yo;
	double		xo;
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
	end = fmod(vars->player.rot + M_PI_4 + (M_PI * 2) , M_PI * 2);
	if (ra > end)
		end += (M_PI * 2);
	// if (ra > end)
	// {
	// 	double buff = ra;
	// 	ra = end;
	// 	end = buff;
	// }
	//printf("Start:%f|End:%f\n", ra, end);
	// if (ra < 0.0)
	// {
	// 	ra = (M_PI * 2 )+ ra;
	// 	end = ra;
	// 	ra = vars->player.rot + M_PI_4;
	// 	printf("Start:%f|End:%f\n", ra, end);
	// }
	while (ra < end)
	{
		i++;
		disV.x = 1e30;
		disV.y = 1e30;
		disH.x = 1e30;
		disH.y = 1e30;
		dof = 0;
		ra2 =  fmod(ra , M_PI * 2);
		aTan = -1.0/tan(ra2);
		if (ra2 > M_PI) //looking down
		{
			ry = (((int)vars->player.pos.y>>shift)<<shift) - .00001;
			rx = (vars->player.pos.y - ry) * aTan + vars->player.pos.x;
			yo = -vars->min_map_mult;
			xo = vars->min_map_mult * aTan;
		}
		if (ra2 < M_PI && ra2 != 0) //looking up
		{
			ry = (((int)vars->player.pos.y>>shift)<<shift) + vars->min_map_mult;
			rx = (vars->player.pos.y - ry) * aTan + vars->player.pos.x;
			yo = vars->min_map_mult;
			xo = -vars->min_map_mult * aTan;
		}
		if (ra2 == 0.0 || ra2 == M_PI)//looking straight left or right
		{
			rx = vars->player.pos.x;
			ry = vars->player.pos.y;
			dof = size;
		}
		while (dof < size)
		{
			mx = (int)rx>>shift;
			my = (int)ry>>shift;
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
			rx = (((int)vars->player.pos.x>>shift)<<shift) - .00001;
			ry = (vars->player.pos.x - rx) * nTan + vars->player.pos.y;
			xo = -vars->min_map_mult;
			yo = vars->min_map_mult * nTan;
		}
		if (ra2 > M_PI_2 * 3.0 || ra2 < M_PI_2) //looking right
		{
			rx = (((int)vars->player.pos.x>>shift)<<shift) + vars->min_map_mult;
			ry = (vars->player.pos.x - rx) * nTan + vars->player.pos.y;
			xo = vars->min_map_mult;
			yo = -vars->min_map_mult * nTan;
		}
		if (ra2 == M_PI_2 || ra2 == M_PI_2 * 3.0)//looking stra2ight left or right
		{
			rx = vars->player.pos.x;
			ry = vars->player.pos.y;
			dof = size;
		}
		while (dof < size)
		{
			mx = (int)rx>>shift;
			my = (int)ry>>shift;
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
		double ca = vars->player.rot - ra2;
		if (ca < 0)
			ca += M_PI * 2;
		if (ca > M_PI * 2)
			ca -= M_PI * 2;
		min_dist *= cos(ca);
		if (dist(vars->player.pos.x, vars->player.pos.y, disV.x, disV.y, ra2) <
			dist(vars->player.pos.x, vars->player.pos.y, disH.x, disH.y, ra2))
		{
			if (ra2 > M_PI)
			{
				color = gen_color(255, 0, 0, 0);
				line_texture(vars, i, fmod(rx, 64.0) * vars->textures.img_so.size.x / (size * 1.0),
					min_dist, &vars->textures.img_so);
				//sud
			}
			else
			{
				color = gen_color(0, 255, 0, 0);
				line_texture(vars, i, fmod(rx, 64.0) * 100.0 / (size * 1.0),
					min_dist, &vars->textures.img_no);
				//nord
			}
		}
		else
		{
			//HIT HORIZONTAL
			if (ra2 > M_PI_2 && ra2 < M_PI_2 + M_PI)
			{
				color = gen_color(0, 0, 255, 0);
				line_texture(vars, i, fmod(ry, 64.0) * 100.0 / (size * 1.0),
					min_dist, &vars->textures.img_ea);
				//est
			}
			else
			{
				color = gen_color(255, 255, 0, 0);
				line_texture(vars, i, fmod(ry, 64.0) * 100.0 / (size * 1.0),
					min_dist, &vars->textures.img_we);
				//ouest
			}
		}
		// if (ra2 == fmod(vars->player.rot - M_PI_4 + (M_PI * 2) , M_PI * 2))
		if (i == vars->win_size.x / 2)
		{
			printf("%.2f %.2f	%d %d	%.2f %.2f %.2f\n", rx, ry,
				(int)rx / size, (int)ry / size, fmod(rx, 64.0) * 100.0 / 64.0, fmod(ry, 64.0) * 100.0 / 64.0, min_dist);
			plot_line(vars,
					gen_coord(vars->player.pos.x + size, size + vars->player.pos.y, 0, gen_color(10, 10, 10, 200)),
					gen_coord(rx + size, size + ry, 0, gen_color(10, 10, 10, 200)));

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
			pixel_put(&vars->img, dx,
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
			pixel_put(&vars->img, dx,
					dy, to_rgb(p.c, 0));
	}
}

void	draw_2d_map(t_vars *vars, int size)
{
	int	x;
	int	y;
	int	pos;
	int x1;
	int y1;

	y = -1;
	pos = -1;
	x1 = 0;
	y1 = 0;
	while (++y < vars->size.y)
	{
		x = -1;
		while (++x < vars->size.x && ++pos >= 0)
		{
			//printf("%c", vars->map[x + y * vars->size.x]);
		if (y >= (((int)vars->player.pos.y / (int)size) - 1) && y <= (((int)vars->player.pos.y / (int)size) + 1)&&
			x >= (((int)vars->player.pos.x / (int)size) - 1) && x <= (((int)vars->player.pos.x / (int)size) + 1))
		{
			if (vars->map[pos] == '0')
				draw_square(vars, gen_coord(x * size + size, y * size + size, size, gen_color(100, 100, 100, 0)));
			else if (vars->map[pos] == '1')
				draw_square(vars, gen_coord(x * size + size, y * size + size, size, gen_color(200, 200, 200, 0)));
			else if (vars->map[pos] == 'O')
				draw_square(vars, gen_coord(x * size + size, y * size + size, size,
					gen_color(150, 20, 150, 0)));
			// if (x1 == 2)
			// {
			// 	x1 = 0;
			// 	y1++;
			// }
		}
		else
			draw_square(vars, gen_coord(x1 * size + size, y1 * size + size, size, vars->textures.c));
		}
	}
		//printf("\n");
}

void	render(t_vars *vars)
{
	ft_int_memset(vars->img.addr, to_rgb(vars->textures.c, 0),
		vars->img.line_length * vars->win_size.y / 8);
	ft_int_memset(vars->img.addr + vars->img.line_length * vars->win_size.y / 2
		, to_rgb(vars->textures.f, 0), vars->img.line_length * vars->win_size.y / 8);
	project_rays(vars, 64.0);
	draw_2d_map(vars, vars->min_map_mult);
	show_player(vars, vars->min_map_mult);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}
