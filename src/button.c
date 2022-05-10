#include "../inc/cub3D.h"

void	change_ui(void		*v, void	*data)
{
	t_vars	*vars;

	vars = (t_vars *)v;
	vars->ui = *((int*)data);
	if (vars->ui)
		mlx_mouse_show();
	else
		mlx_mouse_hide();
}

void	change_setting(void		*v, void	*dat)
{
	t_vars	*vars;
	int	data;

	data = *((int*)dat);
	vars = (t_vars *)v;
	if (data == 1)
	{
		vars->settings.map_type++;
		if (vars->settings.map_type == 3)
			vars->settings.map_type = 0;
	}
}

t_coords screen_pc(double off, double wh, t_rgb colore, t_vars *vars)
{
	t_coords res;
	int	width;
	int	height;
	int	off_l;
	int	off_d;

	width = (int)wh;
	height = fmod(wh * 100.0, 100.0);
	off_l = (int)off;
	off_d = fmod(off * 100.0, 100.0);
	res.a.x = vars->win_size.x * off_l / 100;
	res.a.y = vars->win_size.y * off_d / 100;
	res.b.x = res.a.x + (vars->win_size.x * width / 100);
	res.b.y = res.a.y + (vars->win_size.x * height / 100);
	res.a.c = colore;
	//printf("%d|%d|%d\n", res.x, res.y, res.z);
	return (res);
}

void	button(t_vars *vars, t_coords p, char *txt,void (*f)(void*, void*))
{
	int	dy;
	int	dx;
	int	data;
	unsigned int	add;
	t_data	*text;

	text = get_texture(vars, txt + 1, 0);
	dy = p.a.y;
	data = (int)(*txt - '0');
	while (++dy < p.b.y)
	{
		dx = p.a.x;
		while (++dx < p.b.x && dy - p.a.y < 95)
		{
			add =  *(unsigned int *)(text->addr + ((int)(((dx - p.a.x) * text->size.x) / (p.b.x - p.a.x))
						* (text->bits_per_pixel / 8) + ((int)(((dy - p.a.y) * text->size.y) / (p.b.y - p.a.y)) * text->line_length)));
			//printf("%d\\%d|%d\\%d\n", (((dx - p.a.x) * text->size.x) / (p.b.x - p.a.x)), text->size.x, dy - p.a.y, vars->settings.bttext[(int)txt[1]].size.y);
			if (vars->clicked && vars->clicked_co.x >= p.a.x && vars->clicked_co.x <= p.b.x && vars->clicked_co.y >= p.a.y && vars->clicked_co.y <= p.b.y)
				pixel_put(vars->img, dx, dy, add + (10<<8) + (10<<4) + 10);
			else
				pixel_put(vars->img, dx, dy, add);
		}
	}
	(void)txt;
	//printf("%d\n", mlx_string_put(vars->mlx, vars->win,100,100,0xff00ff, "PLAY"));
	if (vars->clicked)
	{
		if (vars->clicked_co.x >= p.a.x && vars->clicked_co.x <= p.b.x)
			if (vars->clicked_co.y >= p.a.y && vars->clicked_co.y <= p.b.y)
				f(vars, &data);
	}
}
