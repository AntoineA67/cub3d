/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glb_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:22:11 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/14 15:11:41 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_imgs(t_vars *vars)
{
	vars->img = ft_calloc(1, sizeof(t_data));
	vars->img2 = ft_calloc(1, sizeof(t_data));
	vars->settings.bttext = ft_calloc(10, sizeof(t_data));
	load_texture(vars, "start", 0, "./textures/pack_blue_pink/start.xpm");
	load_texture(vars, "settings", 0, "./textures/pack_blue_pink/settings.xpm");
	load_texture(vars, "maps", 0, "./textures/pack_blue_pink/maps.xpm");
	load_texture(vars, "textures", 0, "./textures/pack_blue_pink/textures.xpm");
	load_texture(vars, "no", 0, vars->no);
	load_texture(vars, "aaa", 0, "./textures/xpm/ennemie.xpm");
	load_texture(vars, "hp", 0, "./textures/hp.xpm");
	load_texture(vars, "end", 0, "./textures/xpm/dirt.xpm");
	load_texture(vars, "hud", 0, "./textures/hud0.xpm");
	load_texture(vars, "hud1", 0, "./textures/hud1.xpm");
	load_texture(vars, "bullet", 0, "./textures/bullets/bullet.xpm");
	load_texture(vars, "so", 0, vars->so);
	load_texture(vars, "maps", 0, "./textures/pack_blue_pink/maps.xpm");
	load_texture(vars, "ea", 0, "./textures/xpm/banane.xpm");
	load_texture(vars, "we", 0, vars->we);
}

void	fill_vars2(t_vars *vars, int fd)
{
	if (check_map(vars, (int)vars->player.pos.x, (int)vars->player.pos.y))
		exit_err(vars, 1);
	vars->enemies = ft_calloc(vars->usable_cells / 20 + 2, sizeof(t_enemy));
	init_enemies(vars);
	free(vars->parse_seen);
	init_bullets(vars);
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
	vars->min_map_mult = 16.0;
	vars->ui = 1;
	vars->n1 = gettime(0);
	vars->jump = -2000;
	vars->ao = 1.0;
	vars->ao_scale = .22;
	vars->settings.y_ratio_mouse_speed = 1.2;
	vars->settings.x_ratio_mouse_speed = 1.2;
	affect_ascii(vars);
	ft_bzero(vars->keyboard, sizeof(vars->keyboard));
	vars->mlx = mlx_init();
	vars->win_size.x = 1920;
	vars->win_size.y = 1080;
	vars->rays = ft_calloc(vars->win_size.x + 1, sizeof(t_ray));
	vars->map = parse(fd, vars, 0);
	vars->tx = (2.0 / vars->win_size.x);
	vars->size.z = vars->size.x * vars->size.y;
	vars->max_size = ft_max(vars->size.x, vars->size.y);
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
