/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:58:30 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/22 21:48:06 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	key_rotate(t_vars *vars, int keycode)
{
	if (keycode == 126)
		vars->rotation.x = (vars->rotation.x + 5 * vars->proj_type) % 360;
	else if (keycode == 125)
		vars->rotation.x = (vars->rotation.x - 5 * vars->proj_type) % 360;
	else if (keycode == 123)
		vars->rotation.z = (vars->rotation.z + 5 * vars->proj_type) % 360;
	else if (keycode == 124)
		vars->rotation.z = (vars->rotation.z - 5 * vars->proj_type) % 360;
}

static void	key_translate(t_vars *vars, int keycode)
{
	if (keycode == 0)
		vars->translate.x += 20;
	if (keycode == 1)
		vars->translate.y -= 20;
	if (keycode == 2)
		vars->translate.x -= 20;
	if (keycode == 13)
		vars->translate.y += 20;
}

static void	key_color(t_vars *vars)
{
	if (vars->color.v)
	{
		vars->color.v = 0;
		vars->color.r = 255;
		vars->color.g = 255;
		vars->color.b = 255;
		return ;
	}
	vars->color.r = 255;
	vars->color.g = 0;
	vars->color.b = 0;
	vars->color.v = 1;
}

static void	switch_projection(t_vars *vars)
{
	if (vars->proj_type == 18)
	{
		vars->proj_type = 1;
		coord(&vars->rotation, -55, 0, -45);
	}
	else
	{
		vars->proj_type = 18;
		coord(&vars->rotation, 0, 0, 0);
	}
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 45 && vars->f == &grad_color)
		vars->f = &base_color;
	else if (keycode == 45)
		vars->f = &grad_color;
	else if (keycode == 9)
		next_color(vars);
	else if (keycode == 11)
		key_color(vars);
	else if (keycode == 49 && vars->rotate)
		vars->rotate = 0;
	else if (keycode == 49)
		vars->rotate = 1;
	else if ((keycode >= 0 && keycode <= 3) || keycode == 13)
		key_translate(vars, keycode);
	else if (keycode == 15)
		reset(vars);
	else if (keycode >= 123 && keycode <= 126)
		key_rotate(vars, keycode);
	else if (keycode == 46)
		switch_projection(vars);
	else if (keycode == 53)
		esc(vars, 0);
	project(vars);
	return (0);
}
