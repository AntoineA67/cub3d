#include "cub3D.h"

void	show_player(t_vars *vars, double size)
NOPROF
{
	size = 16.0;
	if (vars->settings.map_type == 1)
	{
		draw_square_center(vars, gen_coord( size * (vars->player.pos.x + 1),
			size * (vars->player.pos.y + 1), size / 2.0, gen_color(255, 0, 100, 0)));
		plot_line(vars,
			gen_coord( size * (vars->player.pos.x + 1), size* (vars->player.pos.y + 1), 0, gen_color(255, 0, 100, 0)),
			gen_coord( (size * (vars->player.pos.x +1)) + vars->player.delta.x * 10.0,
				 (size * (vars->player.pos.y + 1)) + vars->player.delta.y * 10.0, 0, gen_color(255, 0, 100, 0)));
	}
	else if (vars->settings.map_type == 2)
	{
		size = 64;
		draw_square_center(vars, gen_coord( size * (vars->player.pos.x + 1),
			size * (vars->player.pos.y + 1), size / 2.0, gen_color(255, 0, 100, 0)));
		plot_line(vars,
			gen_coord( size * (vars->player.pos.x + 1), size* (vars->player.pos.y + 1) , 0, gen_color(255, 0, 100, 0)),
			gen_coord( (size * (vars->player.pos.x + 1)) + vars->player.delta.x * 10.0,
				 (size * (vars->player.pos.y + 1)) + vars->player.delta.y * 10.0, 0, gen_color(255, 0, 100, 0)));
	}
	else
	{
		draw_square_center(vars, gen_coord( (200) / 2,
			(200) / 2, size / 2.0, gen_color(255, 0, 100, 0)));
		plot_line(vars,
			gen_coord( (200) / 2, (200) / 2 , 0, gen_color(255, 0, 100, 0)),
			gen_coord( (200) / 2 + vars->player.delta.x * 10.0,
				 (200) / 2 + vars->player.delta.y * 10.0, 0, gen_color(255, 0, 100, 0)));
	}
}

void	draw_mini_circle(t_vars *vars)
NOPROF
{
	int	x;
	int y;
	double pos;

	(void)vars;
	y = -1;
	while (++y < 200)
	{
		x = -1;
		while (++x < 200)
		{
				if (x == 0 && y == 0)
					printf("min%f|%f\n", vars->player.pos.y + (y * 0.02) - 2.0, (vars->player.pos.x + (x * 0.02) - 2.0));
				if (y == 199 && x == 199)
					printf("max%f|%f\n", vars->player.pos.y + (y * 0.02) - 2.0, (vars->player.pos.x + (x * 0.02) - 2.0));
			if (sqrt(pow(x - 100, 2) + pow(y - 100, 2)) < 100)
			{
				pos = (int)(vars->player.pos.y + ((y * 8.0) / 200.0) - 4.0) * vars->size.x;
				pos += (vars->player.pos.x + ((x * 8.0) / 200.0) - 4.0);
				if (vars->map[(int)floor(pos)] == '1')
					pixel_put(vars->img, x, y, to_rgb(gen_color(255,255,255,0), 100));
				else if (vars->map[(int)floor(pos)] == 'C')
					pixel_put(vars->img, x, y, to_rgb(gen_color(0,255,0,0), 0));
				else if (vars->map[(int)floor(pos)] == '0')
					pixel_put(vars->img, x, y, to_rgb(gen_color(0,0,0,0), 0));
				else if (vars->map[(int)floor(pos)] == 'O')
					pixel_put(vars->img, x, y, to_rgb(gen_color(255,255,255,0), 0));
				else
					pixel_put(vars->img, x, y, to_rgb(gen_color(100,100,100,0), 0));
			}
					//printf("%f,%f ", asin(abs(y - ((200) / 2))), acos(abs(x - ((200) / 2))));
		}
	}
	// printf("\n");
	// exit(1);
}

void	draw_2d_map(t_vars *vars, int size)
{
	int	x;
	int	y;
	int	pos;
	int x1;
	int y1;
	int k;

	y = -1;
	pos = -1;
	x1 = 0;
	y1 = 0;
	k = 0;
	size = 16;
	if (vars->settings.map_type == 0)
	{
		draw_mini_circle(vars);
		return ;
	}
	while (++y < vars->size.y)
	{
		x = -1;
		while (++x < vars->size.x && ++pos >= 0)
		{
			if (vars->settings.map_type == 1)
			{
				if (vars->map[pos] == '0')
					draw_square(vars, gen_coord(x * size + size, y * size + size, size, gen_color(100, 100, 100, 0)));
				else if (vars->map[pos] == '1')
					draw_square(vars, gen_coord(x * size + size, y * size + size, size, gen_color(200, 200, 200, 0)));
				else if (vars->map[pos] == 'O' || vars->map[pos] == 'C')
					draw_square(vars, gen_coord(x * size + size, y * size + size, size,
						gen_color(150, 20, 150, 0)));

			}
			else if (vars->settings.map_type == 2)
			{
				size = 64;
				if (vars->map[pos] == '0')
					draw_square(vars, gen_coord(x * size + size, y * size + size, size, gen_color(100, 100, 100, 0)));
				else if (vars->map[pos] == '1')
					draw_square(vars, gen_coord(x * size + size, y * size + size, size, gen_color(200, 200, 200, 0)));
				else if (vars->map[pos] == 'O' || vars->map[pos] == 'C')
					draw_square(vars, gen_coord(x * size + size, y * size + size, size,
						gen_color(150, 20, 150, 0)));
			}
		}
	}
}