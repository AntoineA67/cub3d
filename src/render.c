/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:54:13 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/29 14:15:31 by qroussea         ###   ########lyon.fr   */
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
	int			size;
	t_vector2	disV;
	t_vector2	disH;

	size = 64;
	i = -1;
	ra = 0;
	while (ra < M_PI * 2.0)
	{
		disV.x = 1e30;
		disV.y = 1e30;
		disH.x = 1e30;
		disH.y = 1e30;
		dof = 0;
		aTan = -1/tan(ra);
		if (ra > M_PI) //looking down
		{
			ry = (((int)vars->player.pos.y>>6)<<6) - .0001;
			rx = (vars->player.pos.y - ry) * aTan + vars->player.pos.x;
			yo = -64.0;
			xo = 64.0 * aTan;
		}
		else if (ra < M_PI && ra != 0) //looking up
		{
			ry = (((int)vars->player.pos.y>>6)<<6) + 64.0;
			rx = (vars->player.pos.y - ry) * aTan + vars->player.pos.x;
			yo = 64.0;
			xo = -64.0 * aTan;
		}
		else if (ra == 0 || ra == M_PI)//looking straight left or right
		{
			rx = vars->player.pos.x;
			ry = vars->player.pos.y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)rx>>6;
			my = (int)ry>>6;
			mp = my * vars->size.x + mx;
			printf("mx, my, mp: %d %d, %d\n", mx, my, mp);
			if (mp < vars->size.x * vars->size.y && mp > 0 && vars->map[mp] == '1')
				dof = 8;
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
		nTan = -tan(ra);
		if (ra > M_PI_2 && ra < M_PI_2 * 3) //looking left
		{
			rx = (((int)vars->player.pos.x>>6)<<6) - .0001;
			ry = (vars->player.pos.x - rx) * nTan + vars->player.pos.y;
			xo = -64.0;
			yo = 64.0 * nTan;
		}
		else if (ra > M_PI_2 * 3 || ra < M_PI_2) //looking right
		{
			rx = (((int)vars->player.pos.x>>6)<<6) + 64.0;
			ry = (vars->player.pos.x - rx) * nTan + vars->player.pos.y;
			xo = 64.0;
			yo = -64.0 * nTan;
		}
		else if (ra == M_PI_2 || ra == M_PI_2 * 3)//looking straight left or right
		{
			rx = vars->player.pos.x;
			ry = vars->player.pos.y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)rx>>6;
			my = (int)ry>>6;
			mp = my * vars->size.x + mx;
			printf("mx, my, mp: %d %d, %d\n", mx, my, mp);
			if (mp < vars->size.x * vars->size.y && mp > 0 && vars->map[mp] == '1')
				dof = 8;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		disH.x = rx;
		disH.y = ry;
		// if (sqrt(disH.x * disH.x))
		printf("%d HIT: %.2f %.2f	%3d %3d\n", i, rx, ry, (((int)rx>>6)), (((int)ry>>6)));
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

// void	project_rays(t_vars *vars)
// {
// 	int			i;
// 	int			hit;
// 	t_vector2	dpos;
// 	int			size;

// 	i = -1920 / 2;
// 	hit = 0;
// 	size = 64;
// 	while (++i <  -1920 / 2 + 1)
// 	{
// 		dpos.x = vars->player.pos.x;
// 		dpos.y = vars->player.pos.y;
// 		while (!hit)
// 		{
// 			dpos.x += cos(vars->player.rot) / 100;
// 			dpos.y += sin(vars->player.rot) / 100;
			
// 			printf("	Dpos: %3d %3d\n", (((int)dpos.x>>6)), (((int)dpos.y>>6)));
// 			printf("	fDpos: %.2f %.2f\n", dpos.x, dpos.y);
// 			if (vars->map[(((int)dpos.x>>6)) + ((int)dpos.y>>6) * vars->size.x] == '1')
// 				hit = 1;
// 		}
// 		// vars->player.delta.x = dpos.x;
// 		// vars->player.delta.y = dpos.y;
// 		plot_line(vars,
// 			gen_coord(vars->player.pos.x + size, 1080 - vars->size.y * size + vars->player.pos.y, 0),
// 			gen_coord(dpos.x + size,
// 			1080 - vars->size.y * size + dpos.y, 0));
// 		printf("%d HIT: %.2f %.2f	%3d %3d\n", i, dpos.x, dpos.y, (((int)dpos.x>>6)), (((int)dpos.y>>6)));
// 	}
// }

void	draw_2d_map(t_vars *vars, int size)
{
	int	x;
	int	y;

	y = -1;
	while (++y < vars->size.y)
	{
		x = -1;
		while (++x < vars->size.x)
			draw_square(vars, gen_coord(x * size + size, y * size + size, size),
				to_rgb(gen_color(0, 0, 0), (vars->map[x + y * vars->size.x] > 0) * 150
					+ (vars->map[x + y * vars->size.x] > 48) * 50
					+ (vars->map[x + y * vars->size.x] > 49) * 50));
	}
	show_player(vars, size);
}

void	render(t_vars *vars)
{
	// t_coord	p1;
	// t_coord	p2;
	ft_int_memset(vars->img.addr, 0x1D1443,
		vars->img.line_length * 1080 / 4);
	// plot_line(vars, coord(&p1, 0, 0, 0), coord(&p2, 100, 200, 0));
	calculate_plane_points(vars);
	draw_2d_map(vars, 64);
	project_rays(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}
