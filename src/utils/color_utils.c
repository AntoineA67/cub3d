/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:45:52 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/10 17:49:26 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	color(t_rgb *c, int r, int g, int b)
{
	c->r = r;
	c->g = g;
	c->b = b;
}

t_rgb	gen_color(int r, int g, int b, int v)
{
	t_rgb	c;

	c.r = r;
	c.g = g;
	c.b = b;
	c.v = v;
	return (c);
}

unsigned int	to_rgb(t_rgb c, unsigned char grey)
{
	if (grey)
		return (c.v << 24 | grey << 16 | grey << 8 | grey);
	return (c.v << 24 | c.r << 16 | c.g << 8 | c.b);
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
