/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manage_load.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:45:45 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/25 14:22:10 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	replace_texture(t_vars	*vars, int nb, char *path, t_textures	**act)
{
	int		i;
	t_data	**tmp;
	t_data	*actt;

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
		tmp = ft_calloc(sizeof(t_data *), i + 2);
		ft_memcpy(tmp, (*act)->imgtab, i * sizeof(t_data *));
		free((*act)->imgtab);
		(*act)->imgtab = tmp;
	}
	(*act)->imgtab[i] = ft_calloc(1, sizeof(t_data));
	actt = (*act)->imgtab[i];
	actt->img = mlx_xpm_file_to_image(vars->mlx, path,
			&actt->size.x, &actt->size.y);
	actt->addr = mlx_get_data_addr(actt->img, &actt->bits_per_pixel,
			&actt->line_length, &actt->endian);
}

void	new_texture(t_vars	*vars, char *name, t_textures	**act, char *path)
{
	t_data		*actt;
	t_textures	*last;

	last = ft_calloc(sizeof(t_textures), 1);
	last->name = name;
	last->imgtab = ft_calloc(sizeof(t_data *), 2);
	last->imgtab[0] = ft_calloc(sizeof(t_data), 1);
	actt = last->imgtab[0];
	actt->img = mlx_xpm_file_to_image(vars->mlx, path,
			&actt->size.x, &actt->size.y);
	if (!actt->img)
		exit_err(vars, 1);
	actt->addr = mlx_get_data_addr(actt->img, &actt->bits_per_pixel,
			&actt->line_length, &actt->endian);
	if (*act)
		(*act)->next = last;
	else
		*act = last;
	printf("%s:LOADED at :%d\n", name, 0);
}

void	load_texture(t_vars	*vars, char *name, int nb, char *path)
{
	t_textures	**act;

	printf("LOADING:%s\t...\n", path);
	if (access(path, F_OK) == -1)
		exit_err(vars, 1);
	act = &vars->textures;
	if (*act)
		printf("%s, ", (*act)->name);
	while ((*act) && (*act)->next
		&& ft_strncmp((*act)->name, name, ft_strlen(name)))
	{
		act = &(*act)->next;
		printf("%s, ", (*act)->name);
	}
	if (!(*act) || ft_strncmp((*act)->name, name, ft_strlen(name)))
		new_texture(vars, name, act, path);
	else
	{
		replace_texture(vars, nb, path, act);
		printf("%s:REPLACE at :%d\n", name, nb);
	}
}

void	load_animtexture(t_vars	*vars, char *name, int nb, char *path)
{
	int		i;
	char	*pathn;
	char	*buff;
	char	*buff2;

	i = 0;
	while (i < nb)
	{
		pathn = ft_substr(path, 0, ft_strlen(path) - 4);
		buff2 = ft_itoa(i);
		buff = ft_strjoin(pathn, buff2);
		free(pathn);
		free(buff2);
		pathn = ft_strjoin(buff, ".xpm");
		free(buff);
		load_texture(vars, name, i, pathn);
		free(pathn);
		i++;
	}
}
