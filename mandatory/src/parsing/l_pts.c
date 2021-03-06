/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_l_pts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:05:21 by arangoni          #+#    #+#             */
/*   Updated: 2022/01/24 02:10:12 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	exit_lst(t_list **lst)
{
	perror("Map error");
	ft_lstclear(lst, &ft_freetab);
	exit(EXIT_FAILURE);
}

void	fill_lst(t_list **lst, int fd, t_vars *vars)
{
	char		*l;
	t_list		*node;

	node = *lst;
	l = get_next_line(fd);
	if (!l)
		exit_lst(lst);
	while (l)
	{
		if (elem_textures(l, vars))
			break ;
		else
		{
			free(l);
			l = get_next_line(fd);
		}
	}
	while (l)
	{
		node->next = ft_lstnew(l);
		node = node->next;
		if (!node || !*(char *)node->content)
			exit_lst(lst);
		l = get_next_line(fd);
	}
}

char	*create_l_pts(t_list *lst, int size_x, int size_y)
{
	char	*l_pts;
	t_list	*node;

	l_pts = ft_calloc(size_x * size_y + 1, sizeof(char));
	if (!l_pts)
		return (NULL);
	node = lst->next;
	while (node)
	{
		ft_strlcat(l_pts, node->content, -1);
		node = node->next;
	}
	ft_lstclear(&lst, &free);
	return (l_pts);
}

char	*rotate_map(t_vars *vars)
{
	int		y;
	int		x;
	char	*r_map;

	y = -1;
	r_map = ft_calloc(vars->size.x * vars->size.y + 1, sizeof(char));
	if (!r_map)
		exit_err(vars, 1, "Malloc error");
	while (++y < vars->size.y)
	{
		x = -1;
		while (++x < vars->size.x)
			r_map[(vars->size.x - 1 - x)
				* vars->size.y + y] = vars->map[x + vars->size.x * y];
	}
	return (r_map);
}
