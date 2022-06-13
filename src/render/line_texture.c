/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:36:27 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/11 12:38:47 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	line_texture_draw(t_vars *vars, int draw_end, int i, double	y, t_data *img, int screen_x, double ao, int img_x, double			step)
{
	unsigned int	oui;
	unsigned int	*add;
	double			isize;

	isize = 1.0 / (img->size.y + 1.0);
	while (++i < draw_end)
	{
		oui = add_shade(vars, *(unsigned int *)(img->addr + (img_x
						+ (int)y * img->line_length)),
				(int)(vars->rays[screen_x].dist * 10.0),
				vars->ao * (ao + (1 - sin((((y + 1) * isize)) * M_PI))
					* vars->ao_scale));
		add = (unsigned int *)(vars->img->addr
				+ (i * vars->img->line_length + screen_x
					* vars->img->bits_per_pixel));
		*(add) = oui;
		y += step;
	}
}

void line_texture_calc(t_vars *vars, t_data *img, int img_x, double wall_height, int screen_x, double ao)
{
	int				draw_end;
	int				i;
	double			y;
	double			step;
	int				dsy;

	dsy = vars->win_size.y / 2 ;
	if (wall_height < 2)
		wall_height = 0;
	y = 0.0;
	step = (img->size.y + .0) / (2 * wall_height);
	i = dsy - wall_height - vars->player.rot.y - (vars->jump_height / vars->rays[screen_x].dist);
	if (i < 0)
	{
		y = step * (-i);
		i = -1;
	}
	if (img_x < 0)
		img_x = 0;
	if (y < 0.0)
		y = 0.0;
	if (img_x > img->size.x)
		return ;
	img_x *= 4;
	draw_end = dsy + wall_height - vars->player.rot.y - (vars->jump_height / vars->rays[screen_x].dist);
	if (draw_end > vars->win_size.y)
		draw_end = vars->win_size.y;
	line_texture_draw(vars , draw_end, i, y, img, screen_x, ao * vars->ao_scale, img_x, step);
}

void	line_texture(t_vars *vars, int x, int rot, double ao)
{
	int		img_x;
	t_data	*img;

	if (rot == 0)
	{
		img = get_animtexture(vars, "no", 0.2);
		img_x = (vars->rays[x].rx - (int)vars->rays[x].rx) * (img->size.x + .0);
	}
	if (rot == 1)
	{
		img = get_animtexture(vars, "so", 0.2);
		img_x = (vars->rays[x].rx - (int)vars->rays[x].rx) * (img->size.x + .0);
	}
	if (rot == 2)
	{
		img = get_animtexture(vars, "we", 0.2);
		img_x = (vars->rays[x].ry - (int)vars->rays[x].ry) * (img->size.x + .0);
	}
	if (rot == 3)
	{
		img = get_animtexture(vars, "ea", 0.2);
		img_x = (vars->rays[x].ry - (int)vars->rays[x].ry) * (img->size.x + .0);
	}
	line_texture_calc(vars, img, img_x,
		vars->win_size.y / 2 / vars->rays[x].dist * .90, x, ao);
}
