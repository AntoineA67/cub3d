/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 14:23:34 by arangoni          #+#    #+#             */
/*   Updated: 2021/11/08 17:11:55 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*c;

	if (!lst || !f)
		return (NULL);
	new = NULL;
	while (lst)
	{
		c = ft_lstnew(f(lst->content));
		if (!c)
		{
			ft_lstclear(&new, del);
			return (new);
		}
		ft_lstadd_back(&new, c);
		lst = lst->next;
	}
	return (new);
}
