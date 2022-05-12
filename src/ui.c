#include "../inc/cub3D.h"

int	ui_frame1(t_vars	*vars)
{ 
	button(screen_pc(25.15,50.05, gen_color(255,0,100, 100), vars), "start", &change_ui, 0);
	button(screen_pc(25.30,25.025, gen_color(255,255,100, 0), vars), "maps", &change_ui, 2);
	button(screen_pc(25.40,25.025, gen_color(25,60,100, 0), vars), "textures", &change_ui, 3);
	button(screen_pc(25.50,25.025, gen_color(56,69,10, 0), vars), "settings", &change_ui, 4);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

int	ui_frame2(t_vars	*vars)
{ 
	int fd;
	char	*str;
	double off;
	int i;

	fd = open("maps.txt", O_RDONLY);
	str = "MAPS:";
	off = 30.10;
	i = -1;
	while (str && off < 30.90)
	{
		button(screen_pc(off,20.025, gen_color(0,0,0, 255), vars), NULL, &change_map, i);
		img_text(vars, str, screen_pc(off,20.025, gen_color(255,0,100, 0), vars));
		off += 0.10;
		i++;
		str = get_next_line(fd);
	}
	close(fd);
	button(screen_pc(80.80,05.05, gen_color(255,0,100, 0), vars), "start", &change_ui, 1);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}
int	ui_frame3(t_vars	*vars)
{ 
	button(screen_pc(80.80,05.05, gen_color(255,0,100, 0), vars), "start", &change_ui, 1);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

int	ui_setting(t_vars	*vars)
{
	button(screen_pc(80.80,05.05, gen_color(255,0,100, 0), vars), "start", &change_ui, 1);
	button(screen_pc(25.30,25.025, gen_color(255,0,100, 0), vars), "start", &change_setting, 1);
	img_text(vars, ft_strjoin("Minimaps_type: ", ft_itoa(vars->settings.map_type)), screen_pc(60.30,20.025, gen_color(255,0,100, 0), vars));
	slider(vars, screen_pc(25.40,25.025, gen_color(255,0,100, 0), vars), slider_param(120.0, 1.0, &vars->settings.fps_cap), 1.0);
	img_text(vars, ft_strjoin("FPS_CAPS: ", ft_itoa(vars->settings.fps_cap)), screen_pc(60.40,20.025, gen_color(255,0,100, 0), vars));
	slider(vars, screen_pc(25.50,25.025, gen_color(255,0,100, 0), vars), slider_param(1.6, 0.2, &vars->settings.y_ratio_mouse_speed), 0.1);
	img_text(vars, ft_strjoin("Sensibilite Y: ", ft_dtoa(vars->settings.y_ratio_mouse_speed)), screen_pc(60.50,20.025, gen_color(255,0,100, 0), vars));
	slider(vars, screen_pc(25.60,25.025, gen_color(255,0,100, 0), vars), slider_param(2.0, 0.1, &vars->settings.x_ratio_mouse_speed), 0.1);
	img_text(vars, ft_strjoin("Sensibilite X: ", ft_dtoa(vars->settings.x_ratio_mouse_speed)), screen_pc(60.60,20.025, gen_color(255,0,100, 0), vars));
	//slider(vars, screen_pc(25.50,25.025, gen_color(255,0,100, 0), vars), slider_param(0.2, 1.6, &vars->settings.y_ratio_mouse_speed), 0.1);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}