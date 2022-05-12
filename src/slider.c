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
	double	diffx;
	double new;

	(void)pas;
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
	p.a.x += (int)round((((*(double *)slider.setting - slider.min) * diffx) / slider.max) - ((diffx / 10.0) / 2.0));
	while (dy < p.b.y)
	{
		dx = p.a.x;
		while (++dx < p.a.x + diffx / 10)
			pixel_put(vars->img, dx, dy, to_rgb(p.a.c, 200));
		dy++;
	}
	//(void)txt;
	//printf("%d\n", mlx_string_put(vars->mlx, vars->win,100,100,0xff00ff, "PLAY"));
	if (vars->slider == (int)slider.setting)
	{
		p.a.x += (diffx / 10.0) / 2.0;
		mlx_mouse_get_pos(vars->win, &vars->clicked_co.x, &vars->clicked_co.y);
		new = ((((vars->clicked_co.x) - p.a.x) * slider.max) / diffx) - remainder(((((vars->clicked_co.x) - p.a.x) * slider.max) / diffx), pas);
		if ((vars->clicked_co.x > p.a.x + 5 || vars->clicked_co.x < p.a.x - 5 ))
		{
			if (new && *(double *)slider.setting + new <= slider.max && *(double *)slider.setting + new >= slider.min)
				*(double *)slider.setting += new;
			else if (*(double *)slider.setting + pas <= slider.max && *(double *)slider.setting - pas >= slider.min)
				*(double *)slider.setting += pas * ((vars->clicked_co.x < p.a.x - 5) * -1);
		}
	}
	else if (vars->clicking)
	{
		if (vars->clicked_co.x >= p.a.x && vars->clicked_co.x <= p.a.x + diffx / 10)
			if (vars->clicked_co.y >= p.a.y && vars->clicked_co.y <= p.b.y)
				vars->slider = (int)slider.setting;
	}
}