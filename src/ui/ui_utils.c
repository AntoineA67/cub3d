/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:38:56 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/10 13:33:15 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_coords	screen_pc(double off, double wh, t_rgb colore, t_vars *vars)
{
	t_coords	res;
	int			width;
	int			height;
	int			off_l;
	int			off_d;

	width = (int)wh;
	height = (int)fmod(wh * 100.0, 100.0);
	off_l = (int)off;
	off_d = (int)fmod(off * 100.0, 100.0);
	res.a.x = vars->win_size.x * off_l / 100;
	res.a.y = vars->win_size.y * off_d / 100;
	res.b.x = res.a.x + (vars->win_size.x * width / 100);
	res.b.y = res.a.y + (vars->win_size.y * height / 100);
	res.a.c = colore;
	res.vars = vars;
	return (res);
}

void	set_text(t_vars *vars, int data)
{
	char	**text;

	text = ft_split("no.so.ea.we.oui", '.');
	vars->changetexture = ft_strdup(text[data]);
	ft_freetab((void *)text);
}
