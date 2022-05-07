/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:42:07 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/07 17:38:40 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// static t_coord	*cp_l_pts(t_coord *l_pts)
// {
// 	t_coord	*mod_l_pts;
// 	int		i;

// 	mod_l_pts = ft_calloc(l_pts[0].z + 1, sizeof(t_coord));
// 	if (!mod_l_pts)
// 	{
// 		free(l_pts);
// 		exit(EXIT_FAILURE);
// 	}
// 	i = -1;
// 	while (++i < l_pts[0].z + 1)
// 	{
// 		mod_l_pts[i].x = l_pts[i].x;
// 		mod_l_pts[i].y = l_pts[i].y;
// 		mod_l_pts[i].z = l_pts[i].z;
// 		mod_l_pts[i].c.r = l_pts[i].c.r;
// 		mod_l_pts[i].c.g = l_pts[i].c.g;
// 		mod_l_pts[i].c.b = l_pts[i].c.b;
// 		mod_l_pts[i].c.v = l_pts[i].c.v;
// 	}
// 	return (mod_l_pts);
// }

int	init_player(t_vars *vars)
{
	char	*player_in_map;

	vars->player.rot.x = vars->start_rot;
	vars->player.rot.y = 0;
	vars->player.delta.x = 0;
	vars->player.delta.y = 0;
	player_in_map = ft_strchr(vars->map, 'P');
	vars->map[player_in_map - vars->map] = '0';
	vars->player.pos.x = (player_in_map - vars->map) % vars->size.x + .5;
	vars->player.pos.y = (player_in_map - vars->map) / vars->size.x + .5;
	return (0);
}


void	load_texture(t_vars	*vars , char *name, int nb, char *path)
{
	t_data		*actt;
	t_textures	**act;
	t_textures	*last;
	int i;

	printf("LOADING:%s\t...\n", path);
	act = &vars->textures;
	if (*act)
		printf("%s, ", (*act)->name);
	while ((*act) && (*act)->next && ft_strncmp((*act)->name, name, ft_strlen(name)))
	{
		act = &(*act)->next;
		printf("%s, ", (*act)->name);
	}
	if (!(*act) || ft_strncmp((*act)->name, name, ft_strlen(name)))
	{
		last = ft_calloc(sizeof(t_textures), 1);
		last->name = name;
		last->texture = ft_calloc(sizeof(t_data), 2);
		actt = &last->texture[0];
		actt->img = mlx_xpm_file_to_image(vars->mlx, path,
				&actt->size.x, &actt->size.y);
		actt->addr = mlx_get_data_addr(actt->img, &actt->bits_per_pixel,
				&actt->line_length, &actt->endian);
		if (*act)
			(*act)->next = last;
		else
			*act = last;
	}
	else
	{
		i = 0;
		while (i < nb)
			i++;
		// if (!(&((*act)->texture[i])))
		// {
			//printf("load%d|%d\n", i, nb);
			void *tmp = ft_calloc(sizeof(t_data), i + 1);
			ft_memcpy(tmp, (*act)->texture, i * sizeof(t_data));
			free((*act)->texture);
			(*act)->texture = tmp;
		// }
		// else
		// 	ft_bzero((*act)->texture + (i * sizeof(t_data)), sizeof(t_data));
		actt = &((*act)->texture[i]);
		actt->img = mlx_xpm_file_to_image(vars->mlx, path,
			&actt->size.x, &actt->size.y);
		actt->addr = mlx_get_data_addr(actt->img, &actt->bits_per_pixel,
			&actt->line_length, &actt->endian);
	}
	if (!ft_strncmp((*act)->name, name, ft_strlen(name)))
		printf("%s:REPLACE at :%d\n", name, nb);
	else
		printf("%s:LOADED at :%d\n", name, nb);
}

void	load_animtexture(t_vars	*vars , char *name, int nb, char *path)
{
	int	i;
	char	*pathn;

	i = 0;
	while (i < nb)
	{
		pathn = ft_strjoin(ft_substr(path, 0, ft_strlen(path) - 4)  , ft_itoa(i));
		pathn = ft_strjoin(pathn, ".xpm");
		load_texture(vars, name, i, pathn);
		free(pathn);
		i++;
	}
}

void	free_textures(t_vars *vars)
{
	t_textures	*act;

	while (vars->textures)
	{
		act = vars->textures;
		while (act->next)
			act = act->next;
		free(act->texture);
		free(act);
	}
}

t_data	*get_texture(t_vars	*vars, char	*name, int nb)
{
	// t_data		*actt;
	t_textures	*act;
	int i;

	act = vars->textures;
	while (act && ft_strncmp(act->name, name, ft_strlen(name)) && act->next)
		act = act->next;
	if (!ft_strncmp(act->name, name, ft_strlen(name)))
	{
		i = 0;
	//	if (!ft_strncmp(act->name, "player", ft_strlen(name)))
		//	printf("%d\n", act->texture[1].size.x);
		while (i < nb && (&(act->texture[i]) != NULL))
		{
			i++;
		}
		//printf("etdtstfdsfuugvdf%d\n", i);
		return (&(act->texture[i]));
	}
	printf("NOT FOUND:%s\n", name);
	free_textures(vars);
	exit(1);
	return (NULL);
}

int	get_animsize(t_vars	*vars, char *name)
{
	// t_data		*actt;
	t_textures	*act;
	int i;

	act = vars->textures;
	while (act && ft_strncmp(act->name, name, ft_strlen(name)) && act->next)
		act = act->next;
	if (act && !ft_strncmp(act->name, name, ft_strlen(name)))
	{
		i = 0;
		// printf("etdtstfdsfuugvdf%d\n", ft_strlen(act->texture));
		// return (ft_strlen(act->texture ) - 3);
		while ((act->texture + (i * sizeof(t_data))) != NULL)
		{
			i++;
		}
	//	printf("etdtstfdsfuugvdf%d\n", i);
		return (i);
	}
	return (0);
}

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

t_data	*get_animtexture(t_vars	*vars, char	*name, double speed)
{
	t_data *r;

//	printf("TIME:%f\n", gettime(vars->n1) / 1000.0);
//	printf("IM_NUM:%f\n", (speed * 3));
//	printf("SEARCH:%d\n", (int)fmod((gettime(vars->n1) / 1000.0), (speed * 3)));
	r = get_texture(vars, name, floor(fmod((gettime(vars->n1) / 1000.0), (speed * 3.0)) / speed));
	//printf("YES%d\n", r->size.x);
	return (r);
}


void	init_imgs(t_vars *vars)
{
	// t_textures	*imgs;

	vars->img = ft_calloc(1, sizeof(t_data));
	vars->img2 = ft_calloc(1, sizeof(t_data));
	vars->settings.bttext = ft_calloc(10, sizeof(t_data));
	load_texture(vars, "start", 0, "./textures/pack_blue_pink/start.xpm");
	load_texture(vars, "settings", 0, "./textures/pack_blue_pink/settings.xpm");
	load_texture(vars, "maps", 0, "./textures/pack_blue_pink/maps.xpm");
	load_texture(vars, "textures", 0, "./textures/pack_blue_pink/textures.xpm");
	load_animtexture(vars, "player", 4, "./textures/nice/photo.xpm");
	load_texture(vars, "no", 0, vars->no);
	// load_texture(vars, "oui", 0, "./textures/xpm/pho.xpm");
	load_texture(vars, "so", 0, vars->so);
	load_texture(vars, "maps", 0, "./textures/pack_blue_pink/maps.xpm");
	load_texture(vars, "ea", 0, vars->ea);
	load_texture(vars, "we", 0, vars->we);
}

static void	fill_vars(t_vars *vars, int fd)
{
	vars->ao = 1.0;
	vars->ao_scale = .22;
	vars->y_ratio_mouse_speed = 1.2;
	vars->mult_fd = 0;
	ft_bzero(vars->keyboard, sizeof(vars->keyboard));
	vars->mult_n_players = 0;
	vars->mlx = mlx_init();
	vars->win_size.x = 1920;// * 0.75;
	vars->win_size.y = 1080;// * 0.75;
	vars->map = parse(fd, vars);
	if (init_player(vars))
		return ; //NO PLAYER IN MAP
	init_imgs(vars);
	vars->img->img = mlx_new_image(vars->mlx, vars->win_size.x, vars->win_size.y);
	vars->img->addr = mlx_get_data_addr(vars->img->img, &vars->img->bits_per_pixel,
	 		&vars->img->line_length, &vars->img->endian);
	if (!vars->img->addr)
		return ;
	vars->img->bits_per_pixel /= 8;
	vars->img2->img = mlx_new_image(vars->mlx, vars->win_size.x, vars->win_size.y);
	vars->img2->addr = mlx_get_data_addr(vars->img2->img, &vars->img2->bits_per_pixel,
	 		&vars->img2->line_length, &vars->img2->endian);
	if (!vars->img2->addr)
		return ;
	vars->img2->bits_per_pixel /= 8;
	close(fd);
	// mlx_mouse_hide();
	// mlx_mouse_move(vars->win, 0, 0);
}

static char	*extract_name(char *str)
{
	if (ft_strrchr(str, '/'))
		return ((char *)(ft_strrchr(str, '/') + 1));
	return (str);
}

static int	test_hook(t_vars *vars)
{
	(void)vars;
	exit(EXIT_SUCCESS);
	// esc(vars, 0);
	return (0);
}

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

int	ui_frame1(t_vars	*vars)
{ 
	button(vars, screen_pc(25.15,50.05, gen_color(255,0,100, 100), vars), "0start", &change_ui);
	button(vars, screen_pc(25.30,25.025, gen_color(255,255,100, 0), vars), "2maps", &change_ui);
	button(vars, screen_pc(25.40,25.025, gen_color(25,60,100, 0), vars), "3textures", &change_ui);
	button(vars, screen_pc(25.50,25.025, gen_color(56,69,10, 0), vars), "4settings", &change_ui);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

int	ui_frame2(t_vars	*vars)
{ 
	button(vars, screen_pc(80.80,05.05, gen_color(255,0,100, 0), vars), "1start", &change_ui);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}
int	ui_frame3(t_vars	*vars)
{ 
	button(vars, screen_pc(80.80,05.05, gen_color(255,0,100, 0), vars), "1start", &change_ui);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}
int	ui_frame4(t_vars	*vars)
{ 
	button(vars, screen_pc(80.80,05.05, gen_color(255,0,100, 0), vars), "1start", &change_ui);
	button(vars, screen_pc(25.30,25.025, gen_color(255,0,100, 0), vars), "1start", &change_setting);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

int	frame(void *data)
{
	t_vars	*vars;
	long	temp;
	char	*fps;
	char	*itoa;

	vars = (t_vars *)data;
	if (!vars->ui)
	{
	if (!vars->settings.fps_cap || !(gettime(vars->n1) % (1000 / vars->settings.fps_cap)))
	{
		render(vars);
		temp = gettime(vars->n1);
		itoa = ft_itoa(1000 / (temp - vars->n2));
		fps = ft_strjoin("FPS: ", itoa);
		mlx_string_put(vars->mlx, vars->win, 100, 100, 0xff00ff, fps);
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
		ui_frame4(vars);
		vars->clicked = 0;
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
	vars.min_map_mult = 16.0;
	vars.ui = 1;
	fill_vars(&vars, fd);
	(void)extract_name;
	vars.rays_number = 0;
	vars.settings.fps_cap = 60;
	vars.settings.map_type = 1;
	vars.win = mlx_new_window(vars.mlx, vars.win_size.x,
			vars.win_size.y, extract_name(argv[1]));
	printf("EA: %s\nNO: %s\nSO: %s\nWE: %s\nF: %#x\nC: %#x\n",
		vars.ea, vars.no, vars.so, vars.we, to_rgb(vars.f, 0), to_rgb(vars.c, 0));
	// raycasting(&vars);
	// if (!vars.win)
	// 	esc(&vars, 1);
	//mlx_key_hook(vars.win, key_hook, &vars);
	mlx_do_key_autorepeatoff(vars.mlx);
	mlx_hook(vars.win, ON_KEYDOWN, 0, key_hook_down, &vars);
	mlx_hook(vars.win, ON_KEYUP, 0, key_hook_up, &vars);
	mlx_hook(vars.win, ON_DESTROY, 0, test_hook, &vars);
	mlx_loop_hook(vars.mlx, frame, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	// mlx_loop_hook(vars.mlx, raycasting, &vars);
	vars.n1 = gettime(0);
	mlx_loop(vars.mlx);
	free_textures(&vars);
}
