/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glb_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:22:11 by qroussea          #+#    #+#             */
/*   Updated: 2022/07/21 15:05:37 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_imgs(t_vars *vars)
{
	vars->img = ft_calloc(1, sizeof(t_data));
	vars->img2 = ft_calloc(1, sizeof(t_data));
	load_texture(vars, "no", 0, vars->no);
	load_texture(vars, "so", 0, vars->so);
	load_texture(vars, "ea", 0, vars->ea);
	load_texture(vars, "we", 0, vars->we);
}

void	fill_vars2(t_vars *vars, int fd)
{
	// if (check_map(vars, (int)vars->player.pos.x, (int)vars->player.pos.y))
	// 	exit_err(vars, 1);
	// for (int i = 0; i < vars->size.y; i++)
	// {
	// 	write(1, &vars->map[i * vars->size.x], vars->size.x);
	// 	write(1, "\n", 1);
	// }
	// char *r_map = rotate_map(vars);
	// int	sx = vars->size.x;
	// int sy = vars->size.y;
	// vars->size.x = sy;
	// vars->size.y = sx;
	// for (int i = 0; i < vars->size.y; i++)
	// {
	// 	write(1, &r_map[i * vars->size.x], vars->size.x);
	// 	write(1, "\n", 1);
	// }
	// vars->size.x = sx;
	// vars->size.y = sy;
	
	free(vars->parse_seen);
	init_imgs(vars);
	vars->img->img = mlx_new_image(vars->mlx, vars->win_size.x,
			vars->win_size.y);
	if (!vars->img->img)
		exit_err(vars, 1);
	vars->img->addr = mlx_get_data_addr(vars->img->img,
			&vars->img->bits_per_pixel,
			&vars->img->line_length, &vars->img->endian);
	if (!vars->img->addr)
		exit_err(vars, 1);
	vars->img->bits_per_pixel /= 8;
	vars->img2->img = mlx_new_image(vars->mlx, vars->win_size.x,
			vars->win_size.y);
	vars->img2->addr = mlx_get_data_addr(vars->img2->img,
			&vars->img2->bits_per_pixel,
			&vars->img2->line_length, &vars->img2->endian);
	if (!vars->img2->addr)
		exit_err(vars, 1);
	vars->img2->bits_per_pixel /= 8;
	close(fd);
}

void	fill_vars(t_vars *vars, int fd)
{
	ft_bzero(vars, sizeof(t_vars));
	ft_bzero(vars->keyboard, sizeof(vars->keyboard));
	vars->mlx = mlx_init();
	vars->win_size.x = 1920;
	vars->win_size.y = 1080;
	vars->rays = ft_calloc(vars->win_size.x + 1, sizeof(t_ray));
	vars->map = parse(fd, vars, 0);
	vars->tx = (2.0 / vars->win_size.x);
	vars->size.z = vars->size.x * vars->size.y;
	vars->max_size = 100;
	if (init_player(vars))
		exit_err(vars, 1);
	vars->parse_seen = ft_calloc(vars->size.z + 1, 1);
	if (!vars->parse_seen)
		exit_err(vars, 1);
	fill_vars2(vars, fd);
}

char	*extract_name(char *str)
{
	if (ft_strrchr(str, '/'))
		return ((char *)(ft_strrchr(str, '/') + 1));
	return (str);
}
