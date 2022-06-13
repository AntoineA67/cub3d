/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:42:07 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/13 13:08:55 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

long	gettime(long initime)
{
	long			res;
	struct timeval	time;

	gettimeofday(&time, NULL);
	res = time.tv_usec / 1000;
	res += time.tv_sec * 1000;
	res -= initime;
	return (res);
}

static int	test_hook(t_vars *vars)
{
	(void)vars;
	exit(EXIT_SUCCESS);
	// esc(vars, 0);
	return (0);
}

int	frame(void *data)
{
	t_vars	*vars;
	long	temp;
	char	*fps;
	char	*itoa;

	vars = (t_vars *)data;
	check_inputs(vars);
	if (vars->mult_fd)
		serv_process(vars);
	if (!vars->ui)
	{
		temp = gettime(vars->n1);
		vars->delta_time = (temp + .0 - (vars->n3 + .0)) / 1000.0;
		vars->n3 = temp;
		if (!vars->settings.fps_cap || !fmod(gettime(vars->n1), (1000 / (int)vars->settings.fps_cap)))
		{
			vars->delta_time_render = (temp + .0 - (vars->n2 + .0)) / 1000.0;
			itoa = ft_itoa(1000 / (temp - vars->n2));
			fps = ft_strjoin("FPS: ", itoa);
			render(vars);
			mlx_string_put(vars->mlx, vars->win, 100, 100, 0xff00ff, fps);
			img_text_simple(vars, fps, gen_coord(vars->win_size.x - 100, 10, 4, gen_color(255, 255, 255, 0)));
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img2, 0, 0);
			free(itoa);
			free(fps);
			vars->n2 = temp;
		}
	}
	else
	{
		ft_int_memset(vars->img->addr, 0x000000,
		vars->img->line_length * vars->win_size.y / 4);
		if (vars->ui == 1)
		{
			ui_frame1(vars);
			vars->clicked = 0;
		}
		else if (vars->ui == 2)
		{
			ui_frame2(vars);
			vars->clicked = 0;
		}
		else if (vars->ui == 3)
		{
			ui_frame3(vars);
			vars->clicked = 0;
		}
		else if (vars->ui == 4)
		{
			ui_setting(vars);
			vars->clicked = 0;
		}
		else if (vars->ui == 5)
		{
			ui_texture(vars);
			vars->clicked = 0;
		}
		else if (vars->ui == 11)
		{
			if (gettime(vars->n1) - vars->n2 > 5000)
			{
				free_textures(vars);
				exit(0);
			}
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		fd;

	if (argc != 2)
	{
		perror("Argument error");
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("File error");
		exit(EXIT_FAILURE);
	}
	ft_bzero(&vars, sizeof(t_vars));
	vars.min_map_mult = 16.0;
	vars.ui = 1;
	vars.n1 = gettime(0);
	fill_vars(&vars, fd);
	(void)extract_name;
	vars.settings.map_type = 1;
	vars.win = mlx_new_window(vars.mlx, vars.win_size.x,
			vars.win_size.y, extract_name(argv[1]));
	printf("EA: %s\nNO: %s\nSO: %s\nWE: %s\nF: %#x\nC: %#x\n",
		vars.ea, vars.no, vars.so, vars.we, to_rgb(vars.f, 0), to_rgb(vars.c, 0));
	mlx_do_key_autorepeatoff(vars.mlx);
	mlx_hook(vars.win, ON_KEYDOWN, 0, key_hook_down, &vars);
	mlx_hook(vars.win, ON_KEYUP, 0, key_hook_up, &vars);
	mlx_hook(vars.win, ON_MOUSEUP, 0, mouse_hook_up, &vars);
	mlx_hook(vars.win, ON_DESTROY, 0, test_hook, &vars);
	mlx_loop_hook(vars.mlx, frame, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	// mlx_loop_hook(vars.mlx, raycasting, &vars);
	mlx_loop(vars.mlx);
	free_textures(&vars);
}
