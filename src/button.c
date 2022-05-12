#include "../inc/cub3D.h"

void	change_map(void		*v, int data)
{
	t_vars	*vars;

	vars = (t_vars *)v;
	int fd;
	char	*str;
	int i;

	fd = open("maps.txt", O_RDONLY);
	str = get_next_line(fd);
	i = 0;
	while (str)
	{
		if (i == data)
		{
			str = ft_strjoin("maps/", str);
			printf("{%s}\n", vars->map);
			free(vars->map);
			vars->map = NULL;
			if (str[ft_strlen(str) - 1] == '\n')
				str[ft_strlen(str) - 1] = 0;
			i = open(str, O_RDONLY);
			vars->map = parse(i, vars);
			printf("{%s}\n", vars->map);
			if (init_player(vars))
				return ; //NO PLAYER IN MAP
			//free(str);
		}
		i++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	change_ui(vars, 1);
}

void	change_texture(void		*v, int data)
{
	t_vars	*vars;

	vars = (t_vars *)v;
	int fd;
	char	*str;
	int i;

	fd = open("textures.txt", O_RDONLY);
	str = get_next_line(fd);
	i = 0;
	while (str)
	{
		if (i == data)
		{
			if (str[ft_strlen(str) - 1] == '\n')
				str[ft_strlen(str) - 1] = 0;
			printf("Load:%s| to |%s|\n", str, vars->changetexture);
			load_texture(vars, vars->changetexture, 0, str);
		}
		i++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	change_ui(vars, 1);
}


void	change_ui(void		*v, int data)
{
	t_vars	*vars;

	vars = (t_vars *)v;
	vars->ui = data;
	vars->scroll = 0;
	if (vars->ui)
		mlx_mouse_show();
	else
	{
		mlx_mouse_hide();
		mlx_mouse_move(vars->win, vars->win_size.x / 2, vars->win_size.y / 2);
	}
}

void	change_setting(void		*v, int	data)
{
	t_vars	*vars;

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
	res.vars = vars;
	//printf("%d|%d|%d\n", res.x, res.y, res.z);
	return (res);
}

void	button(t_coords p, char *txt,void (*f)(void*, int), int data)
{
	int	dy;
	int	dx;
	unsigned int	add;
	t_data	*text;

	if (txt)
		text = get_texture(p.vars, txt, 0);
	dy = p.a.y;
	while (++dy < p.b.y)
	{
		dx = p.a.x;
		while (++dx < p.b.x && dy - p.a.y < 95)
		{
			if (txt)
				add =  *(unsigned int *)(text->addr + ((int)(((dx - p.a.x) * text->size.x) / (p.b.x - p.a.x))
							* (text->bits_per_pixel / 8) + ((int)(((dy - p.a.y) * text->size.y) / (p.b.y - p.a.y)) * text->line_length)));
			else
				add = to_rgb(p.a.c, 0);
			if (p.vars->clicked && p.vars->clicked_co.x >= p.a.x && p.vars->clicked_co.x <= p.b.x && p.vars->clicked_co.y >= p.a.y && p.vars->clicked_co.y <= p.b.y)
				pixel_put(p.vars->img, dx, dy, add + (10<<8) + (10<<4) + 10);
			else
				pixel_put(p.vars->img, dx, dy, add);
		}
	}
	//printf("%d\n", mlx_string_put(p.vars->mlx, p.vars->win,100,100,0xff00ff, "PLAY"));
	if (p.vars->clicked)
	{
		if (p.vars->clicked_co.x >= p.a.x && p.vars->clicked_co.x <= p.b.x)
			if (p.vars->clicked_co.y >= p.a.y && p.vars->clicked_co.y <= p.b.y)
				f(p.vars, data);
	}
}
