/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:27:43 by arangoni          #+#    #+#             */
/*   Updated: 2021/11/08 12:01:26 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*c;

	if (!new)
		return ;
	if (!(*alst))
	{
		*alst = new;
		return ;
	}
	c = *alst;
	while (c && c->next)
		c = c->next;
	c->next = new;
}
