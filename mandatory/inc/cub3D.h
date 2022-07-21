/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 20:48:46 by arangoni          #+#    #+#             */
/*   Updated: 2022/07/21 14:37:24 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include "../../libft/libft.h"
# include "../../mlx_opengl/mlx.h"

# define MAX_BULLETS 2000
# define M_2PI 6.283185307179586

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
	int				run;
	t_vector2		pos;
	t_vector2		delta;
	t_vector2		rot;
	int				lives;
}		t_player;

typedef struct s_textures
{
	t_data				**imgtab;
	char				*name;
	struct s_textures	*next;
}	t_textures;

typedef struct s_ray {
	t_vector2	start_pos;
	double		dist;
	double		rx;
	double		ry;
	double		ra2;
	int			side;
}		t_ray;

typedef struct s_ltextcalc
{
	int		draw_end;
	int		i;
	double	y;
	t_data	*img;
	int		screen_x;
	double	ao;
	int		img_x;
	double	step;
	double	wall_height;
}	t_ltextcalc;

typedef struct s_vars {
	t_ray			*rays;
	int				max_size;
	double			tx;
	double			rotmpi;
	double			start;
	double			end;
	int				usable_cells;
	char			*parse_seen;
	char			keyboard[300];
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
	char			*changetexture;
	float			start_rot;
	int				clicked;
	int				clicking;
	t_coord			clicked_co;
	t_vector2		camera;
}			t_vars;

typedef struct s_coords
{
	t_coord	a;
	t_coord	b;
	t_vars	*vars;
}		t_coords;

typedef struct s_line {
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e_d;
	float	dist;
}		t_line;

//************************* Texture manage fonctions *************************//

void			load_texture(t_vars	*vars, char *name, int nb, char *path);
void			load_animtexture(t_vars	*vars, char *name, int nb, char *path);
void			free_textures(t_vars *vars);
t_data			*get_texture(t_vars	*vars, char	*name, int nb);
int				get_animsize(t_vars	*vars, char *name);

//******************************* Init *******************************//

int				init_player(t_vars *vars);
void			fill_vars(t_vars *vars, int fd);
char			*extract_name(char *str);

//**************************** Parsing Functions *****************************//

int				ft_strschr(char *s, char *finds);
int				ft_strnschr(char *s, char *finds);
int				str_to_rgb(t_vars *vars, t_rgb *col, char *str);
char			*create_l_pts(t_list *lst, int size_x, int size_y);
void			fill_lst(t_list **lst, int fd, t_vars *vars);
char			*parse(int fd, t_vars *vars, int len_tmp);
int				check_map(t_vars *vars, char *maps);
void			line_texture(t_vars *vars, int screen_x, char *t);
int				elem_textures(char *l, t_vars *vars);

//**************************** Moving Functions ******************************//

void			move_player(t_vars *vars, int dir_x, int dir_y);
int				mouse_hook_up(int keycode, int x, int y, t_vars *vars);
void			rotate_player_x(t_vars *vars, int dir);
int				check_inputs(t_vars *vars);
int				key_hook_down(int keycode, t_vars *vars);
int				key_hook_up(int keycode, t_vars *vars);
int				mouse_hook(int keycode, int x, int y, t_vars *vars);

//***************************** Draw Functions *******************************//

void			pixel_put(t_data *data, int x, int y, unsigned int color);
int				is_in_window(t_vars *vars, int x, int y);
unsigned int	to_rgb(t_rgb c, unsigned char grey);
void			pixel_put_add(t_data *data, int *x, int *y, unsigned int *colo);

//**************************** Render Functions ******************************//

double			dist(double ax, double ay, double bx, double by);
void			render(t_vars *vars);
void			calc_ray(t_vars *vars, t_ray *r);
void			project_rays(t_vars *vars);

//********************************************* ******************************//

void			exit_err(t_vars *vars, int err);

#endif