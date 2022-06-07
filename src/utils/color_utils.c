/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:45:52 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/02 15:59:18 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	color(t_rgb *c, int r, int g, int b)
NOPROF
{
	c->r = r;
	c->g = g;
	c->b = b;
}

t_rgb	gen_color(int r, int g, int b, int v)
NOPROF
{
	t_rgb	c;

	c.r = r;
	c.g = g;
	c.b = b;
	c.v = v;
	return (c);
}

unsigned int	to_rgb(t_rgb c, unsigned char grey)
NOPROF
{
	if (grey)
		return (c.v << 24 | grey << 16 | grey << 8 | grey);
	return (c.v << 24 | c.r << 16 | c.g << 8 | c.b);
}

t_rgb	cycle_color(t_rgb color)
NOPROF
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

// void	next_color(t_vars *vars)
// {
// 	t_rgb	*c;

// 	c = &vars->color;
// 	if (c->v)
// 		c->v = 0;
// 	if (c->r == 255 && c->g == 255 && c->b == 255)
// 	{
// 		c->g = 0;
// 		c->b = 0;
// 	}
// 	else if (c->r == 255 && c->g < 255 && c->b == 0)
// 		c->g = 255;
// 	else if (c->r == 0 && c->g == 255 && c->b < 255)
// 		c->b = 255;
// 	else if (c->r < 255 && c->g == 0 && c->b == 255)
// 		c->r = 255;
// 	else if (c->r > 0 && c->g == 255 && c->b == 0)
// 		c->r = 0;
// 	else if (c->r == 0 && c->g > 0 && c->b == 255)
// 		c->g = 0;
// 	else if (c->r == 255 && c->g == 0 && c->b > 0)
// 		c->b = 0;
// }
