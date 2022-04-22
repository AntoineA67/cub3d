/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:45:52 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/22 21:48:04 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	color(t_rgb *c, int r, int g, int b)
{
	c->r = r;
	c->g = g;
	c->b = b;
}

int	to_rgb(t_rgb c)
{
	return (0x00 << 24 | c.r << 16 | c.g << 8 | c.b);
}

t_rgb	cycle_color(t_rgb color)
{
	t_rgb	c;

	c.r = color.r;
	c.g = color.g;
	c.b = color.b;
	c.v = color.v;
	if (c.r == 255 && c.g < 255 && c.b == 0)
		c.g += 5;
	else if (c.r == 0 && c.g == 255 && c.b < 255)
		c.b += 5;
	else if (c.r < 255 && c.g == 0 && c.b == 255)
		c.r += 5;
	else if (c.r > 0 && c.g == 255 && c.b == 0)
		c.r -= 5;
	else if (c.r == 0 && c.g > 0 && c.b == 255)
		c.g -= 5;
	else if (c.r == 255 && c.g == 0 && c.b > 0)
		c.b -= 5;
	return (c);
}

void	next_color(t_vars *vars)
{
	t_rgb	*c;

	c = &vars->color;
	if (c->v)
		c->v = 0;
	if (c->r == 255 && c->g == 255 && c->b == 255)
	{
		c->g = 0;
		c->b = 0;
	}
	else if (c->r == 255 && c->g < 255 && c->b == 0)
		c->g = 255;
	else if (c->r == 0 && c->g == 255 && c->b < 255)
		c->b = 255;
	else if (c->r < 255 && c->g == 0 && c->b == 255)
		c->r = 255;
	else if (c->r > 0 && c->g == 255 && c->b == 0)
		c->r = 0;
	else if (c->r == 0 && c->g > 0 && c->b == 255)
		c->g = 0;
	else if (c->r == 255 && c->g == 0 && c->b > 0)
		c->b = 0;
}
