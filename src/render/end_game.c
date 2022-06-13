/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:22:27 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/13 13:10:53 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	end_game_lose(t_vars *vars)
{
	t_rgb	red;

	red = gen_color(255, 0, 0, 0);
	vars->ui = 11;
	ft_int_memset(vars->img->addr, 0x000000,
		vars->img->line_length * vars->win_size.y / 4);
	img_text(vars, "GAME OVER", screen_pc(30.30, 50.50, red, vars));
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	vars->n2 = gettime(vars->n1);
	printf("Game over\n");
}

void	end_game_win(t_vars *vars)
{
	t_rgb	red;

	red = gen_color(255, 0, 0, 0);
	vars->ui = 10;
	ft_int_memset(vars->img->addr, 0x000000,
		vars->img->line_length * vars->win_size.y / 4);
	img_text(vars, "YOU WIN", screen_pc(30.30, 50.50, red, vars));
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	printf("You win\n");
}

int	check_end_game(t_vars *vars)
{
	int	i;

	i = -1;
	if (vars->player.lives <= 0)
	{
		end_game_lose(vars);
		return (1);
	}
	while (++i < vars->max_n_enemies)
		if (vars->enemies[i].lives > 0)
			return (0);
	end_game_win(vars);
	return (1);
}
