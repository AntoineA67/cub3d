/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:01:30 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/06 12:57:07 by qroussea         ###   ########lyon.fr   */
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

	// printf("%s\n", str);
	splitted = ft_split(str, ',');
	i = -1;
	while (splitted[++i])
	{
		// if (err_format_rgb(splitted[i]) || i > 2)
		// {
		// 	printf("error\n");
		// 	return 1; //TODO GESTION ERREUR	
		// }
	}
	col->r = ft_atoi(splitted[0]);
	col->g = ft_atoi(splitted[1]);
	col->b = ft_atoi(splitted[2]);
	// printf("%d %d %d\n", col->r, col->g, col->b);
	return (0);
}

int	elem_textures(char **l, t_vars *vars, int fd)
{
	char	*t;

	t = *l;
	if (**l == '\n' && !*(t + 1))
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

static void	fill_lst(t_list **lst, int fd, t_vars *vars)
{
	char		*l;
	t_list		*node;

	node = *lst;
	l = get_next_line(fd);
	if (!l)
		exit_lst(lst);
	while (l)
		if (elem_textures(&l, vars, fd))
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

int	ft_strschr(char *s, char *finds)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (finds && finds[i])
	{
		if (ft_strchr(s, finds[i]))
			return (i);
		i++;
	}
	return (0);
}

char	*parse(int fd, t_vars *vars)
{
	t_list	*lst;
	t_list	*node;
	int		len_tmp;
	char *tmp;

	tmp = "ENWS";
	lst = ft_lstnew(NULL);
	if (!lst)
		exit(EXIT_FAILURE);
	fill_lst(&lst, fd, vars);
	node = lst->next;
	vars->size.x = 0;
	vars->size.y = 0;
	while (node && node->content)
	{
		printf("d:%s\n", node->content);
		if (ft_strschr(node->content, tmp))
		{
			vars->start_rot = M_PI_2 * ft_strschr(node->content, tmp);
			*ft_strchr(node->content, tmp[ft_strschr(node->content, tmp)]) = 'P';
		}
		len_tmp = ft_strlen((char *)node->content);
		if (((char *)node->content)[len_tmp - 1] == '\n')
			((char *)node->content)[len_tmp - 1] = 0;
		len_tmp = ft_strlen((char *)node->content);
		if (len_tmp > vars->size.x)
			vars->size.x = len_tmp;
		vars->size.y++;
		node = node->next;
	}
	node = lst->next;
	while (node && node->content)
	{
		if ((int)ft_strlen((char *)node->content) < vars->size.x)
		{
			tmp = ft_calloc(sizeof(char), vars->size.x + 1);
			ft_memset(tmp, ' ', vars->size.x);
			ft_strlcpy(tmp, node->content, ft_strlen((char *)node->content) + 1);
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
