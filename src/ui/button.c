/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:05:40 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/13 13:34:36 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	change_map(t_vars *vars, int data)
{
	int		fd;
	char	*str;
	int		i;

	fd = open("maps.txt", O_RDONLY);
	str = get_next_line(fd);
	i = -1;
	while (str && ++i >= 0)
	{
		if (i == data)
		{
			str = ft_strjoin("maps/", str);
			printf("{%s}\n", vars->map);
			free(vars->map);
			vars->map = NULL;
			if (str[ft_strlen(str) - 1] == '\n')
				str[ft_strlen(str) - 1] = 0;
			i = open(str, O_RDONLY);
			vars->map = parse(i, vars, 0);
			printf("{%s}\n", vars->map);
			if (init_player(vars))
				return ;
		}
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	change_ui(vars, 1);
}

void	change_texture(t_vars *vars, int data)
{
	int		fd;
	char	*str;
	int		i;

	fd = open("textures.txt", O_RDONLY);
	str = get_next_line(fd);
	i = -1;
	while (str && ++i >= 0)
	{
		if (i == data)
		{
			if (str[ft_strlen(str) - 1] == '\n')
				str[ft_strlen(str) - 1] = 0;
			printf("Load:%s| to |%s|\n", str, vars->changetexture);
			if (!ft_strchr(str, '@'))
				load_texture(vars, vars->changetexture, 0, str);
			else
				load_animtexture(vars, vars->changetexture,
					ft_atoi(str), str + (ft_strchr(str, '@') - str) + 1);
		}
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	change_ui(vars, 1);
}

void	change_ui(t_vars *vars, int data)
{
	vars->ui = data;
	vars->scroll = 0;
	if (vars->ui)
		mlx_mouse_show();
	else
	{
		mlx_mouse_hide();
		mlx_mouse_move(vars->win, vars->win_size.x / 2, vars->win_size.y / 2);
	}
}

void	change_setting(t_vars *vars, int data)
{
	if (data == 1)
	{
		vars->settings.map_type++;
		if (vars->settings.map_type == 3)
			vars->settings.map_type = 0;
	}
}

void	button(t_coords p, char *txt, void (*f)(t_vars *, int), int data)
{
	int				dy;
	int				dx;
	unsigned int	add;
	t_data			*text;

	if (txt)
		text = get_texture(p.vars, txt, 0);
	dy = p.a.y;
	while (++dy < p.b.y)
	{
		dx = p.a.x;
		while (++dx < p.b.x)
		{
			if (txt)
				add = *(unsigned int *)(text->addr
						+ ((int)(((dx - p.a.x) * text->size.x) / (p.b.x - p.a.x))
							* (text->bits_per_pixel / 8) + ((int)floor(((dy - p.a.y) * text->size.y) / (p.b.y - p.a.y)) * text->line_length)));
			else
				add = to_rgb(p.a.c, 0);
			if (p.vars->clicked && p.vars->clicked_co.x >= p.a.x && p.vars->clicked_co.x <= p.b.x && p.vars->clicked_co.y >= p.a.y && p.vars->clicked_co.y <= p.b.y)
				pixel_put(p.vars->img, dx, dy, add + (10<<8) + (10<<4) + 10);
			else
				pixel_put(p.vars->img, dx, dy, add);
		}
	}
	if (p.vars->clicked)
	{
		if (p.vars->clicked_co.x >= p.a.x && p.vars->clicked_co.x <= p.b.x)
			if (p.vars->clicked_co.y >= p.a.y && p.vars->clicked_co.y <= p.b.y)
				f(p.vars, data);
	}
}
