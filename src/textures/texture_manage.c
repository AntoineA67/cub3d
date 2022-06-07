#include "cub3D.h"

void	load_texture(t_vars	*vars , char *name, int nb, char *path)
NOPROF
{
	t_data		*actt;
	t_textures	**act;
	t_textures	*last;
	int i;

	printf("LOADING:%s\t...\n", path);
	if (access(path, F_OK) == -1)
	{
		perror(path);
		free_textures(vars);
		exit(0);
	}
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
		last->imgtab = ft_calloc(sizeof(t_data *), 2);
		last->imgtab[0] = ft_calloc(sizeof(t_data), 1);
		actt = last->imgtab[0];
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
		while ((*act)->imgtab[i])
			i++;
		if ((*act)->imgtab[nb])
		{
			free((*act)->imgtab[nb]);
			i = nb;
		}
		else
		{
			t_data **tmp = ft_calloc(sizeof(t_data *), i + 2);
			ft_memcpy(tmp, (*act)->imgtab, i * sizeof(t_data *));
			free((*act)->imgtab);
			(*act)->imgtab = tmp;
		}
		// }
		// else
		// 	ft_bzero((*act)->imgtab + (i * sizeof(t_data)), sizeof(t_data));
		//printf("CHANGE:%d\n", i);
		(*act)->imgtab[i] = ft_calloc(1, sizeof(t_data));
		actt = (*act)->imgtab[i];
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
NOPROF
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
NOPROF
{
	t_textures	*act;
	t_textures	*last;
	int			i;

	while (vars->textures)
	{
		last = NULL;
		act = vars->textures;
		while (act->next)
		{
			last = act;
			act = act->next;
		}
		while (act->imgtab[0] != NULL)
		{
			i = 0;
			while (act->imgtab[i] != NULL)
				i++;
			if (i)
			{
				free(act->imgtab[i - 1]);
				act->imgtab[i - 1] = NULL;
			}
			else
				free(act->imgtab[0]);
		}
		free(act->imgtab);
		act->imgtab = NULL;
		free(act);
		if (last)
			last->next = NULL;
		else
			vars->textures = NULL;
	}
}

t_data	*get_texture(t_vars	*vars, char	*name, int nb)
NOPROF
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
		while (i < nb && (act->imgtab[i] != NULL))
		{
		//	printf("etdtstfdsfuugvdf%d\n", i);
			i++;
		}
		return (act->imgtab[i]);
	}
	printf("NOT FOUND:%s\n", name);
	free_textures(vars);
	exit(1);
	return (NULL);
}

int	get_animsize(t_vars	*vars, char *name)
NOPROF
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
	//	if (!ft_strncmp(act->name, "player", ft_strlen(name)))
		//printf("%s\n", act->name);
		while (act->imgtab[i] != NULL)
			i++;
		return (i);
	}
	return (0);
}

t_data	*get_animtexture(t_vars	*vars, char	*name, double speed)
NOPROF
{
	t_data *r;

//	printf("TIME:%f\n", gettime(vars->n1) / 1000.0);
//	printf("IM_NUM:%d\n", get_animsize(vars, name));
	//printf("SEARCH:%d\n", (int)fmod((gettime(vars->n1) / 1000.0), (speed * get_animsize(vars, name))));
	r = get_texture(vars, name, floor(fmod((gettime(vars->n1) / 1000.0), (speed * get_animsize(vars, name))) / speed));
	//printf("YES%d\n", r->size.x);
	return (r);
}
