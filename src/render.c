/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:54:13 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/29 18:00:06 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	show_player(t_vars *vars, int size)
{
	draw_square_center(vars, gen_coord(vars->player.pos.x + size,
		size + vars->player.pos.y, 20), to_rgb(gen_color(255, 255, 0), 0));
	// p1.x = ((int)vars->player.pos.x>>6) * size + x;
	// p1.y = ((int)vars->player.pos.y>>6) * size + y;
	// p2.x = (((int)vars->player.pos.x>>6) + vars->player.delta.x) * size + x;
	// p2.y = (((int)vars->player.pos.y>>6) + vars->player.delta.y) * size + y;
	plot_line(vars,
		gen_coord(vars->player.pos.x + size, size + vars->player.pos.y, 0),
		gen_coord(vars->player.pos.x + vars->player.delta.x * 10.0 + size,
			size + vars->player.pos.y + vars->player.delta.y * 10.0, 0));
	// printf("%d %d	%d %d\n", p1.x, p1.y, p2.x, p2.y);
}

double	dist(double ax, double ay, double bx, double by, double angle)
{
	(void)angle;
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	project_rays(t_vars *vars)
{
	int			i;
	int			dof;
	int			mx;
	int			my;
	int			mp;
	double		ra;
	double		aTan;
	double		nTan;
	double		ry;
	double		rx;
	double		yo;
	double		xo;
	double		end;
	int			size;
	t_vector2	disV;
	t_vector2	disH;

	size = 64;
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
		disV.x = 1e30;
		disV.y = 1e30;
		disH.x = 1e30;
		disH.y = 1e30;
		dof = 0;
		double ra2;
		ra2 =  fmod(ra , M_PI * 2);
		aTan = -1.0/tan(ra2);
		if (ra2 > M_PI) //looking down
		{
			ry = (((int)vars->player.pos.y>>6)<<6) - .00001;
			rx = (vars->player.pos.y - ry) * aTan + vars->player.pos.x;
			yo = -64.0;
			xo = 64.0 * aTan;
		}
		if (ra2 < M_PI && ra2 != 0) //looking up
		{
			ry = (((int)vars->player.pos.y>>6)<<6) + 64.0;
			rx = (vars->player.pos.y - ry) * aTan + vars->player.pos.x;
			yo = 64.0;
			xo = -64.0 * aTan;
		}
		if (ra2 == 0.0 || ra2 == M_PI)//looking straight left or right
		{
			rx = vars->player.pos.x;
			ry = vars->player.pos.y;
			dof = 8;
		}
		while (dof < size)
		{
			mx = (int)rx>>6;
			my = (int)ry>>6;
			mp = my * vars->size.x + mx;
			if (mp < vars->size.x * vars->size.y && mp >= 0 && vars->map[mp] == '1')
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
			rx = (((int)vars->player.pos.x>>6)<<6) - .00001;
			ry = (vars->player.pos.x - rx) * nTan + vars->player.pos.y;
			xo = -64.0;
			yo = 64.0 * nTan;
		}
		if (ra2 > M_PI_2 * 3.0 || ra2 < M_PI_2) //looking right
		{
			rx = (((int)vars->player.pos.x>>6)<<6) + 64.0;
			ry = (vars->player.pos.x - rx) * nTan + vars->player.pos.y;
			xo = 64.0;
			yo = -64.0 * nTan;
		}
		if (ra2 == M_PI_2 || ra2 == M_PI_2 * 3.0)//looking stra2ight left or right
		{
			rx = vars->player.pos.x;
			ry = vars->player.pos.y;
			dof = 8;
		}
		while (dof < size)
		{
			mx = (int)rx>>6;
			my = (int)ry>>6;
			mp = my * vars->size.x + mx;
			if (mp < vars->size.x * vars->size.y && mp >= 0 && vars->map[mp] == '1')
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
		if (dist(vars->player.pos.x, vars->player.pos.y, disV.x, disV.y, ra2) <
			dist(vars->player.pos.x, vars->player.pos.y, disH.x, disH.y, ra2))
		{
			rx = disV.x;
			ry = disV.y;
		}
		plot_line(vars,
				gen_coord(vars->player.pos.x + size, size + vars->player.pos.y, 0),
				gen_coord(rx + size, size + ry, 0));
		ra += .1;
	}
}

void	draw_square_center(t_vars *vars, t_coord p, unsigned int color)
{
	int	dy;
	int	dx;

	dy = p.y - p.z / 2;
	while (++dy < p.y + p.z / 2)
	{
		dx = p.x - p.z / 2;
		while (++dx < p.x + p.z / 2)
			pixel_put(&vars->img, dx,
					dy, color);
	}
}

void	draw_square(t_vars *vars, t_coord p, unsigned int color)
{
	int	dy;
	int	dx;

	dy = p.y;
	while (++dy < p.y + p.z)
	{
		dx = p.x;
		while (++dx < p.x + p.z)
			pixel_put(&vars->img, dx,
					dy, color);
	}
}

void	draw_2d_map(t_vars *vars, int size)
{
	int	x;
	int	y;
	int	pos;

	y = -1;
	pos = -1;
	while (++y < vars->size.y)
	{
		x = -1;
		while (++x < vars->size.x && ++pos >= 0)
		{
			//printf("%c", vars->map[x + y * vars->size.x]);
			if (vars->map[pos] == '0')
				draw_square(vars, gen_coord(x * size + size, y * size + size, size),
					to_rgb(gen_color(0, 0, 0), 50));
			else if (vars->map[pos] == '1')
				draw_square(vars, gen_coord(x * size + size, y * size + size, size),
					to_rgb(gen_color(0, 0, 0), 150));
		}
	}
		//printf("\n");
}

void	render(t_vars *vars)
{
	// t_coord	p1;
	// t_coord	p2;
	ft_int_memset(vars->img.addr, 0x1D1443,
		vars->img.line_length * 1080 / 4);
	// plot_line(vars, coord(&p1, 0, 0, 0), coord(&p2, 100, 200, 0));
	draw_2d_map(vars, 64);
	project_rays(vars);
	show_player(vars, 64);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}
