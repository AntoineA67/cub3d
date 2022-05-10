#include "../inc/cub3D.h"

t_slider	slider_param(double	max, double min, void *setting)
{
	t_slider	res;

	res.min = min;
	res.max = max;
	res.setting = setting;
	return (res);
}

void	slider(t_vars *vars, t_coords p, t_slider slider, double pas)
{
	int	dy;
	int	dx;
	int max;
	int min;
	double	diffx;

	max = slider.max / pas;
	min = slider.min / pas;
	diffx = (p.b.x - p.a.x);
	dy = p.a.y + ((p.b.y - p.a.y) / 4);
	while (dy < p.b.y - ((p.b.y - p.a.y) / 4))
	{
		dx = p.a.x;
		while (++dx < p.b.x)
			pixel_put(vars->img, dx, dy, to_rgb(p.a.c, 100));
		dy++;
	}
	dy = p.a.y;
	p.a.x += *(double *)slider.setting * diffx;
	while (dy < p.b.y)
	{
		//printf("Draw:%f\n", *(double *)slider.setting);
		dx = p.a.x;
		while (++dx < p.a.x + (diffx / 10))
			pixel_put(vars->img, dx, dy, to_rgb(p.a.c, 200));
		dy++;
	}
	//(void)txt;
	//printf("%d\n", mlx_string_put(vars->mlx, vars->win,100,100,0xff00ff, "PLAY"));
	if (vars->slider == (unsigned int)slider.setting)
	{
			mlx_mouse_get_pos(vars->win, &vars->clicked_co.x, &vars->clicked_co.y);
		printf("d:%d|%D|%f|%f\n",max,min, (ceil(((vars->clicked_co.x - p.a.x) * max) / diffx) * pas), *(double *)slider.setting + (ceil(((vars->clicked_co.x - p.a.x) * max) / diffx) * pas));
		p.a.x += (diffx / 10) / 2;
		if (vars->clicked_co.x > p.a.x + 5  && vars->clicked_co.x < p.a.x - 5 && *(double *)slider.setting + (ceil(((vars->clicked_co.x - p.a.x) * max) / diffx) * pas) <= slider.max && *(double *)slider.setting + (ceil(((vars->clicked_co.x - p.a.x) * max) / diffx) * pas) >= slider.min)
			*(double *)slider.setting += ceil(((vars->clicked_co.x - p.a.x) * max) / diffx) * pas;
		printf("settings:%f\n", *((double *)slider.setting));
	}
	else if (vars->clicking)
	{
		if (vars->clicked_co.x >= p.a.x && vars->clicked_co.x <= p.a.x + diffx / 10)
			if (vars->clicked_co.y >= p.a.y && vars->clicked_co.y <= p.b.y)
				vars->slider = (unsigned int)slider.setting;
	}
	// printf("settings:%f\n", *(double *)slider.setting);
}
