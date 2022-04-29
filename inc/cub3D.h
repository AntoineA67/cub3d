/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 20:48:46 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/29 19:17:18 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TEX_W 64

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include "../libft/libft.h"
# include "../mlx_opengl/mlx.h"

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
	int	v;
}		t_rgb;

typedef struct s_coord
{
	int		x;
	int		y;
	int		z;
	t_rgb	c;
}		t_coord;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_coord	size;
}			t_data;

typedef struct s_vector2 {
	double	x;
	double	y;
}			t_vector2;

typedef struct s_textures {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_data	img_no;
	t_data	img_so;
	t_data	img_we;
	t_data	img_ea;
	t_rgb	f;
	t_rgb	c;
}			t_textures;

typedef struct s_player {
	t_vector2	pos;
	t_vector2	delta;
	double	rot;
}		t_player;

typedef struct s_vars {
	int				rays_number;
	t_coord			win_size;
	t_player		player;
	t_textures		textures;
	t_data			textures_img[4];
	t_coord			size;
	t_data			img;
	void			*mlx;
	void			*win;
	char			*map;
	double 			rays;
	int				render_dist;
	int				fps_cap;
	int				start_rot;
	long			n1;
	long			n2;
	t_vector2		plane;
	t_vector2		*plane_rays;
	t_vector2		camera;
}			t_vars;

typedef struct s_ray {
	double			camera_x;
	t_vector2			ray_dir;
	t_coord			map_pos;
	t_vector2			side_dist;
	t_vector2			delta_dist;
	double			perp_wall_dist;
	t_coord			step;
	double			tex_pos;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			h;
	int				pitch;
	t_vector2			wall;
	t_coord			tex;
	unsigned int	color;
}		t_ray;

typedef struct s_line {
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e_d;
	float	dist;
}		t_line;

unsigned int	to_rgb(t_rgb c, unsigned char grey);
void	show_player(t_vars *vars, int size);
void	draw_direction(t_vars *vars, int ratio);
void	calculate_plane_points(t_vars *vars);
void	draw_square(t_vars *vars, t_coord p);
void	draw_square_center(t_vars *vars, t_coord p);
int		f_loop(t_vars *vars);
void	render(t_vars *vars);
void	plot_line(t_vars *vars, t_coord p1, t_coord p2);
// int		is_in_window(t_coord *point);
int		key_hook(int keycode, t_vars *vars);
// int		grad_color(t_rgb *c1, t_rgb *c2, float val, t_rgb map_color);
// int		base_color(t_rgb *c1, t_rgb *c2, float val, t_rgb map_color);
// int		mouse_hook(int keycode, int x, int y, t_vars *vars);
// void	out(t_vars *vars);
void	esc(t_vars *vars, int err);
// void	reset(t_vars *vars);
// void	project(t_vars *vars);
// void	exit_lst(t_list **lst);
// void	next_color(t_vars *vars);
// void	color(t_rgb *c, int r, int g, int b);
t_coord	gen_coord(int x, int y, int z, t_rgb c);
t_rgb	gen_color(int r, int g, int b, int v);
t_coord	coord(t_coord *p, int x, int y, int z);

void	pixel_put(t_data *data, int x, int y, int color);
// float	deg_to_rad(int d);
// t_rgb	cycle_color(t_rgb color);
char	*parse(int fd, t_vars *vars);
char	*create_l_pts(t_list *lst, int size_x, int size_y);

#endif