/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:54:13 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/28 16:00:50 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	draw_2d_map(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (++y < vars->size.y)
	{
		x = -1;
		while (++x < vars->size.x)
			pixel_put(&vars->img, x * 10, y * 10, 0xffffff - vars->map[y * vars->size.x + x] * 256);
	}
}

void	render(t_vars *vars)
{
	// t_coord	p1;
	// t_coord	p2;
	
	ft_int_memset(vars->img.addr, 0x1D1443,
		vars->img.line_length * 1080 / 4);
	show_player(vars);
	plot_line(vars, coord(&p1, 0, 0, 0), coord(&p2, 100, 200, 0));
	calculate_plane_points(vars);
	//project_rays(vars, rays);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}
