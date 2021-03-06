/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:01:30 by arangoni          #+#    #+#             */
/*   Updated: 2022/07/28 16:19:06 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_map(t_vars *vars, char *maps)
{
	int	i;

	i = 0;
	if (ft_strnstr(maps, " 0", ft_strlen(maps))
		|| ft_strnstr(maps, "0 ", ft_strlen(maps)))
		exit_err(vars, 1, "Invalid map (error id 1)");
	while (i < (int)(ft_strlen(maps) + 1))
	{
		if (maps[i] == '0' || (i > 0 && maps[i + vars->size.x - 1] == '0'))
			exit_err(vars, 1, "Invalid map (error id 2");
		i += vars->size.x;
	}
	return (0);
}

int	elem_textures(char *l, t_vars *vars)
{
	char	*tmp;

	tmp = ft_strtrim(l, " \t\n");
	if (!ft_strncmp(tmp, "NO ", 3))
		vars->no = ft_strtrim(tmp + 3, "\n ");
	else if (!ft_strncmp(tmp, "SO ", 3))
		vars->so = ft_strtrim(tmp + 3, "\n ");
	else if (!ft_strncmp(tmp, "WE ", 3))
		vars->we = ft_strtrim(tmp + 3, "\n ");
	else if (!ft_strncmp(tmp, "EA ", 3))
		vars->ea = ft_strtrim(tmp + 3, "\n ");
	else if (!ft_strncmp(tmp, "F ", 2))
		str_to_rgb(vars, &vars->f, tmp);
	else if (!ft_strncmp(tmp, "C ", 2))
		str_to_rgb(vars, &vars->c, tmp);
	else if (*l != '\n' && *(l + 1))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

char	*parse_sec(t_vars *vars, t_list	*lst)
{
	t_list	*node;
	char	*tmp;

	node = lst->next;
	while (node && node->content)
	{
		if ((int)ft_strlen((char *)node->content) < vars->size.x)
		{
			tmp = ft_calloc(sizeof(char), vars->size.x + 1);
			ft_memset(tmp, ' ', vars->size.x);
			ft_strlcpy(tmp, node->content,
				ft_strlen((char *)node->content) + 1);
			tmp[ft_strlen((char *)node->content)] = ' ';
			free(node->content);
			node->content = tmp;
		}
		node = node->next;
	}
	if (!vars->no || !vars->so || !vars->we
		|| !vars->ea || !vars->c.v || !vars->f.v)
		exit_err(vars, 1, "Invalid map (error id 3)");
	return (create_l_pts(lst, vars->size.x, vars->size.y));
}

void	calc_len(t_list *node, int *len_tmp, t_vars *vars)
{
	*len_tmp = ft_strlen((char *)node->content);
	if (((char *)node->content)[*len_tmp - 1] == '\n')
		((char *)node->content)[--*len_tmp] = 0;
	if (++vars->size.y && *len_tmp > vars->size.x)
		vars->size.x = *len_tmp;
}

char	*parse(int fd, t_vars *vars, int len_tmp)
{
	t_list	*lst;
	t_list	*node;
	char	*pp;

	pp = "ENWS";
	lst = ft_lstnew(NULL);
	if (!lst)
		exit(EXIT_FAILURE);
	fill_lst(&lst, fd, vars);
	node = lst->next;
	while (node && node->content)
	{
		if (!ft_strnschr(node->content, " 01NSEW\n"))
			exit_err(vars, 1, "Invalid map (error id 4)");
		if (ft_strschr(node->content, pp) >= 0)
		{
			vars->start_rot = M_PI_2 * ft_strschr(node->content, pp);
			*ft_strchr(node->content, pp[ft_strschr(node->content, pp)]) = 'P';
		}
		calc_len(node, &len_tmp, vars);
		node = node->next;
	}
	return (parse_sec(vars, lst));
}
