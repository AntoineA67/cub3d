/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 05:55:10 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/22 21:48:10 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	project_back(t_vars *vars)
{
	int	i;

	i = vars->l_tmp[0].z + 1;
	while (--i - 1)
	{
		if (i % vars->l_tmp[0].x != 1 && (is_in_window(&vars->l_tmp[i])
				|| is_in_window(&vars->l_tmp[i - 1])))
			plot_line(vars, vars->l_tmp[i], vars->l_tmp[i - 1]);
		if (i > vars->l_tmp[0].x && (is_in_window(&vars->l_tmp[i])
				|| is_in_window(&vars->l_tmp[i - vars->l_tmp[0].x])))
			plot_line(vars, vars->l_tmp[i],
				vars->l_tmp[i - vars->l_tmp[0].x]);
	}
}

static void	project_front(t_vars *vars)
{
	int	i;

	i = 0;
	while (++i <= vars->l_tmp[0].z)
	{
		if (i % vars->l_tmp[0].x != 0
			&& (is_in_window(&vars->l_tmp[i])
				|| is_in_window(&vars->l_tmp[i + 1])))
			plot_line(vars, vars->l_tmp[i], vars->l_tmp[i + 1]);
		if (i <= vars->l_tmp[0].z - vars->l_tmp[0].x
			&& (is_in_window(&vars->l_tmp[i])
				|| is_in_window(&vars->l_tmp[i + vars->l_tmp[0].x])))
			plot_line(vars, vars->l_tmp[i],
				vars->l_tmp[i + vars->l_tmp[0].x]);
	}
}

static void	mult_matrix(float matrix[6], t_coord *rotation)
{
	float	rx;
	float	ry;
	float	rz;

	rx = ft_deg_to_rad(rotation->x);
	ry = ft_deg_to_rad(rotation->y);
	rz = ft_deg_to_rad(rotation->z);
	matrix[0] = cos(ry) * cos(rz);
	matrix[1] = cos(ry) * sin(rz);
	matrix[2] = -sin(ry);
	matrix[3] = sin(rx) * sin(ry) * cos(rz) - cos(rx) * sin(rz);
	matrix[4] = sin(rx) * sin(ry) * sin(rz) + cos(rx) * cos(rz);
	matrix[5] = sin(rx) * cos(ry);
}

void	tag(t_vars *vars)
{
	mlx_string_put(vars->mlx, vars->win, 50, 20, 0xffffff, "Rotate: arrows");
	mlx_string_put(vars->mlx, vars->win, 50, 40, 0xffffff, "Move: WASD");
	mlx_string_put(vars->mlx, vars->win, 50, 80, 0xffffff,
		"Change projection type: M");
	mlx_string_put(vars->mlx, vars->win, 50, 100, 0xffffff,
		"Switch map color / custom colors: N");
	mlx_string_put(vars->mlx, vars->win, 50, 120, 0xffffff, "Cycle color: B");
	mlx_string_put(vars->mlx, vars->win, 50, 140, 0xffffff, "Next color: V");
	mlx_string_put(vars->mlx, vars->win, 50, 180, 0xffffff, "Reset view: R");
	mlx_string_put(vars->mlx, vars->win, 50, 200, 0xffffff, "Exit: ESC");
}

void	project(t_vars *vars)
{
	int		i;
	float	r[9];

	ft_int_memset(vars->img.addr, 0x1D1443,
		vars->img.line_length * vars->size.y / 4);
	i = 0;
	mult_matrix(r, &vars->rotation);
	while (++i < vars->l_pts[0].z + 1)
	{
		vars->l_tmp[i].x = (vars->l_pts[i].x * r[0] + vars->l_pts[i].y
				* r[1] + vars->l_pts[i].z * r[2])
			* vars->zoom + vars->translate.x;
		vars->l_tmp[i].y = (vars->l_pts[i].x * r[3] + vars->l_pts[i].y
				* r[4] + vars->l_pts[i].z * r[5])
			* vars->zoom + vars->translate.y;
	}
	if (ft_abs(vars->rotation.z) % 360 > 90
		&& ft_abs(vars->rotation.z) % 360 <= 270)
		project_back(vars);
	else
		project_front(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	tag(vars);
}
