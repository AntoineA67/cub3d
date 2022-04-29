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

#include "../inc/cub3D.h"

// static void	fill_point(t_coord *point, char *s)
// {
// 	char	*find;

// 	point->z = ft_atoi(s);
// 	find = ft_strchr(s, ',');
// 	if (find && *(find) + 1 && *(find) + 2)
// 		point->c.v = ft_max(ft_atoi_base(find + 3, "0123456789abcdef"),
// 				ft_atoi_base(find + 3, "0123456789ABCDEF"));
// 	else
// 		point->c.v = 0xffffff;
// 	point->c.r = (point->c.v / 0x10000) % 0x100;
// 	point->c.g = (point->c.v / 0x100) % 0x100;
// 	point->c.b = point->c.v % 0x100;
// }

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
