/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:01:30 by arangoni          #+#    #+#             */
/*   Updated: 2022/04/22 23:23:29 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	exit_lst(t_list **lst)
{
	perror("Map error");
	ft_lstclear(lst, &ft_freetab);
	exit(EXIT_FAILURE);
}

int	err_format_rgb(char *str)
{
	char	*cpy;
	int		i;

	cpy = ft_strtrim(str, " ");
	if (!cpy)
		return (1); //TODO GESTION ERREUR
	i = -1;
	while (cpy[++i])
		if (!ft_isdigit(cpy[i]))
			return (1);
	free(cpy);
	return (0);
}

int	str_to_rgb(t_rgb *col, char *str)
{
	char	**splitted;
	int		i;

	splitted = ft_split(str, ',');
	i = -1;
	while (splitted[++i])
	{
		if (err_format_rgb(splitted[i]) || i > 2)
			return 1; //TODO GESTION ERREUR	
	}
	col->r = ft_atoi(splitted[0]);
	col->g = ft_atoi(splitted[1]);
	col->b = ft_atoi(splitted[2]);
	return (0);
}

int	elem_textures(char **l, t_textures *textures, int fd)
{
	if (**l == '\n' && !*(*(l + 1)))
	{
		free(*l);
		*l = get_next_line(fd);
		return (0);
	}
	else if (!ft_strncmp(*l, "NO ", 3))
		textures->no = ft_strtrim(*l + 3, "\n ");
	else if (!ft_strncmp(*l, "so ", 3))
		textures->so = ft_strtrim(*l + 3, "\n ");
	else if (!ft_strncmp(*l, "we ", 3))
		textures->we = ft_strtrim(*l + 3, "\n ");
	else if (!ft_strncmp(*l, "ea ", 3))
		textures->ea = ft_strtrim(*l + 3, "\n ");
	else if (!ft_strncmp(*l, "F ", 2))
		str_to_rgb(&textures->f, *l + 2);
	else if (!ft_strncmp(*l, "C ", 2))
		str_to_rgb(&textures->c, *l + 2);
	else
		return (1);
	free(*l);
	*l = get_next_line(fd);
	return (0);
}

static void	fill_lst(t_list **lst, int fd)
{
	char		*l;
	t_list		*node;
	t_textures	textures;

	node = *lst;
	l = get_next_line(fd);
	if (!l)
		exit_lst(lst);
	while (l)
		if (elem_textures(&l, &textures, fd))
			break;
	while (l)
	{
		node->next = ft_lstnew(l);
		node = node->next;
		if (!node || !*(char *)node->content)
			exit_lst(lst);
		l = get_next_line(fd);
	}
}

char	*parse(int fd)
{
	t_list	*lst;
	t_list	*node;
	t_coord	size;

	lst = ft_lstnew(NULL);
	if (!lst)
		exit(EXIT_FAILURE);
	fill_lst(&lst, fd);
	node = lst->next;
	size.x = 0;
	size.y = 0;
	while (node && node->content)
	{
		if ((int)ft_strlen((char *)node->content) > size.x)
			size.x = ft_strlen((char *)node->content);
		size.y++;
		node = node->next;
	}
	printf("x: %d y: %d\n", size.x, size.y);
	return (create_l_pts(lst, size.x, size.y));
}
