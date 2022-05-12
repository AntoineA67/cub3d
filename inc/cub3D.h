/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 20:48:46 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/12 13:51:07 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include "../libft/libft.h"
# include "../mlx_opengl/mlx.h"

# define MAX_CLIENT 10
# define PORT 6300
# define SERVER_IP "127.0.0.1"

enum	e_mlx_events {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

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

typedef struct s_player {
	int			run;
	t_vector2	pos;
	t_vector2	delta;
	t_vector2	rot;
}		t_player;

typedef struct s_settings
{
	double			fps_cap;
	int				map_type;
	double			y_ratio_mouse_speed;
	double			x_ratio_mouse_speed;
	t_data			*bttext;
}	t_settings;

typedef struct s_packet
{
	int				n_players;
	t_vector2		players_pos[MAX_CLIENT];
	double			players_rot[MAX_CLIENT];
}	t_packet;

typedef	struct s_textures
{
	t_data				**imgtab;
	char				*name;
	struct s_textures 	*next;
}	t_textures;

typedef struct s_vars {
	char			*parse_seen;
	uint64_t		font[128];
	double			jump_height;
	time_t			jump;
	int				ao;
	double			ao_scale;
	struct sockaddr_in	serv_addr;
	char			keyboard[300];
	int				mult_fd;
	int				mult_id;
	int				mult_n_players;
	t_vector2		mult_positions[MAX_CLIENT];
	char			buffer[1025];
	int				rays_number;
	t_coord			win_size;
	t_player		player;
	t_textures		*textures;
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	t_rgb			f;
	t_rgb			c;
	t_coord			size;
	t_data			*img;
	t_data			*img2;
	int				img_int;
	void			*mlx;
	void			*win;
	char			*map;
	double 			rays;
	int				start_rot;
	int				ui;
	int				clicked;
	int				clicking;
	int				slider;
	t_coord			clicked_co;
	t_settings		settings;
	double			min_map_mult;
	long			n1;
	long			n2;
	t_vector2		camera;
}			t_vars;

typedef struct s_coords
{
	t_vars	*vars;
	t_coord	a;
	t_coord	b;
}		t_coords;

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

typedef struct s_slider {
	double min;
	double max;
	void *setting;
}	t_slider;

//************************* Texture manage fonctions *************************//

void		load_texture(t_vars	*vars, char *name, int nb, char *path);
void		load_animtexture(t_vars	*vars, char *name, int nb, char *path);
void		free_textures(t_vars *vars);
t_data		*get_texture(t_vars	*vars, char	*name, int nb);
int			get_animsize(t_vars	*vars, char *name);
t_data		*get_animtexture(t_vars	*vars, char	*name, double speed);

//***************************** Button fonctions *****************************//

void		change_ui(void		*v, int data);
void		change_map(void		*v, int data);
void		change_setting(void		*v,  int data);
t_coords	screen_pc(double off, double wh, t_rgb colore, t_vars *vars);
void		button(t_coords p, char *txt,void (*f)(void*, int), int data);

//***************************** Slider fonctions *****************************//

t_slider	slider_param(double	max, double min, void *setting);
void		slider(t_vars *vars, t_coords p, t_slider slider, double pas);

//******************************* UI fonctions *******************************//

int			ui_frame1(t_vars	*vars);
int			ui_frame2(t_vars	*vars);
int			ui_frame3(t_vars	*vars);
int			ui_setting(t_vars	*vars);

//**************************** Minimap fonctions *****************************//

void	show_player(t_vars *vars, double size);
void	draw_2d_map(t_vars *vars, int size);

//****************************************************************************//

int		init_player(t_vars *vars);
double	dist(double ax, double ay, double bx, double by, double angle);
int	check_map(t_vars *vars, int x, int y);
int	mouse_hook_up(int keycode, int x, int y, t_vars *vars);
long	gettime(long initime);
void	img_text(t_vars *vars, char *str, t_coords p);
void	affect_ascii(t_vars *vars);
void	vert_line(t_vars *vars, int x, int size, int color);
void	rotate_player_x(t_vars *vars, int dir);
unsigned int	add_shade(t_vars *vars, unsigned int c, unsigned int dist_int, double ao);
void	print_tab_pos(t_vector2 tab[10]);
int		serv_connect(t_vars *vars);
int		serv_process(t_vars *vars);
unsigned int	to_rgb(t_rgb c, unsigned char grey);
void	show_player(t_vars *vars, double size);
void	draw_direction(t_vars *vars, int ratio);
void	calculate_plane_points(t_vars *vars);
void	draw_square(t_vars *vars, t_coord p);
void	draw_square_center(t_vars *vars, t_coord p);
int		f_loop(t_vars *vars);
void	render(t_vars *vars);
void	plot_line(t_vars *vars, t_coord p1, t_coord p2);
int		is_in_window(t_vars *vars, int x, int y);
int		check_inputs(t_vars *vars);
int	key_hook_down(int keycode, t_vars *vars);
int	key_hook_up(int keycode, t_vars *vars);
// int		grad_color(t_rgb *c1, t_rgb *c2, float val, t_rgb map_color);
// int		base_color(t_rgb *c1, t_rgb *c2, float val, t_rgb map_color);
 int		mouse_hook(int keycode, int x, int y, t_vars *vars);
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
void	line_texture(t_vars *vars, int screen_x, int img_x, t_data *img, double hit_dist, double ao);

void	pixel_put(t_data *data, int x, int y, unsigned int color);
// float	deg_to_rad(int d);
// t_rgb	cycle_color(t_rgb color);
char	*parse(int fd, t_vars *vars);
char	*create_l_pts(t_list *lst, int size_x, int size_y);

#endif