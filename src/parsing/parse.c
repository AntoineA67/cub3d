/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:01:30 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/13 16:48:02 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_map(t_vars *vars, int x, int y)
{
	if (x < 0 || y < 0 || x >= vars->size.x || y >= vars->size.y
		|| vars->map[x + vars->size.x * y] == ' ')
		return (1);
	else if (vars->parse_seen[x + vars->size.x * y])
		return (0);
	if (vars->map[x + vars->size.x * y] == '0'
		|| vars->map[x + vars->size.x * y] == 'C')
	{
		vars->parse_seen[x + vars->size.x * y] = 1;
		vars->usable_cells++;
		return (check_map(vars, x + 1, y) || check_map(vars, x - 1, y)
			|| check_map(vars, x, y + 1) || check_map(vars, x, y - 1));
	}
	return (0);
}

int	elem_textures(char **l, t_vars *vars, int fd)
{
	if (**l == '\n' && !*(*l + 1))
	{
		free(*l);
		*l = get_next_line(fd);
		return (0);
	}
	else if (!ft_strncmp(*l, "NO ", 3))
		vars->no = ft_strtrim(*l + 3, "\n ");
	else if (!ft_strncmp(*l, "SO ", 3))
		vars->so = ft_strtrim(*l + 3, "\n ");
	else if (!ft_strncmp(*l, "WE ", 3))
		vars->we = ft_strtrim(*l + 3, "\n ");
	else if (!ft_strncmp(*l, "EA ", 3))
		vars->ea = ft_strtrim(*l + 3, "\n ");
	else if (!ft_strncmp(*l, "F ", 2))
		str_to_rgb(&vars->f, *l + 2);
	else if (!ft_strncmp(*l, "C ", 2))
		str_to_rgb(&vars->c, *l + 2);
	else
		return (1);
	free(*l);
	*l = get_next_line(fd);
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
			printf("|%s|\n", tmp);
			free(node->content);
			node->content = tmp;
		}
		node = node->next;
	}
	printf("x: %d y: %d\n", vars->size.x, vars->size.y);
	return (create_l_pts(lst, vars->size.x, vars->size.y));
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
		
		if (ft_strschr(node->content, pp) >= 0)
		{
			vars->start_rot = M_PI_2 * ft_strschr(node->content, pp);
			*ft_strchr(node->content, pp[ft_strschr(node->content, pp)]) = 'P';
		}
		len_tmp = ft_strlen((char *)node->content);
		if (((char *)node->content)[len_tmp - 1] == '\n')
			((char *)node->content)[--len_tmp] = 0;
		if (++vars->size.y && len_tmp > vars->size.x)
			vars->size.x = len_tmp;
		printf("d:%s\n", node->content);
		node = node->next;
	}
	return (parse_sec(vars, lst));
}
