/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:54:13 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/28 16:01:05 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	show_player(t_vars *vars)
{
	(void)vars;
	int	i;
	int	j;
	int	size;

	size = 10;
	i = -size;
	while (++i < size)
	{
		j = -size;
		while (++j < size)
		{
			pixel_put(&vars->img, i + vars->player.pos.x * 10,
					j + vars->player.pos.y * 10, 0xffffff);
		}
	}
	draw_direction(vars);
}

void	project_rays(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->rays_number)
	{
		
	}
}

void	draw_2d_map(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (++y < vars->size.y)
	{
		x = -1;
		while (++x < vars->size.x)
			pixel_put(&vars->img, x * 20 + 100, y * 20 + 100, 0xffffff - vars->map[y * vars->size.x + x] * 256);
	}
}

void	render(t_vars *vars)
{
	// t_coord	p1;
	// t_coord	p2;
	
	ft_int_memset(vars->img.addr, 0x1D1443,
		vars->img.line_length * 1080 / 4);
	show_player(vars);
	// plot_line(vars, coord(&p1, 0, 0, 0), coord(&p2, 100, 200, 0));
	calculate_plane_points(vars);
	draw_2d_map(vars);
	//project_rays(vars, rays);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}
