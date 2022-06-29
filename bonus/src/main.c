/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:42:07 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/29 13:19:15 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	test_hook(t_vars *vars)
{
	(void)vars;
	exit(EXIT_SUCCESS);
	return (0);
}

int	frame(void *data)
{
	t_vars	*vars;

	vars = (t_vars *)data;
	check_inputs(vars);
	render(vars);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		fd;

	if (argc != 2 || !ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		exit_err(&vars, 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		exit_err(&vars, 1);
	}
	fill_vars(&vars, fd);
	(void)extract_name;
	vars.win = mlx_new_window(vars.mlx, vars.win_size.x,
			vars.win_size.y, extract_name(argv[1]));
	mlx_do_key_autorepeatoff(vars.mlx);
	mlx_mouse_hide();
	mlx_hook(vars.win, ON_KEYDOWN, 0, key_hook_down, &vars);
	mlx_hook(vars.win, ON_KEYUP, 0, key_hook_up, &vars);
	mlx_hook(vars.win, ON_MOUSEUP, 0, mouse_hook_up, &vars);
	mlx_hook(vars.win, ON_DESTROY, 0, test_hook, &vars);
	mlx_loop_hook(vars.mlx, frame, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop(vars.mlx);
	free_textures(&vars);
}
