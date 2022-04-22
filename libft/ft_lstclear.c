/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:45:50 by arangoni          #+#    #+#             */
/*   Updated: 2021/11/08 11:42:08 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	c;

	if (!lst)
		return ;
	while (*lst)
	{
		c = **lst;
		ft_lstdelone(*lst, del);
		*lst = c.next;
		if (c.next)
			c = *c.next;
	}
	lst = NULL;
}
