/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:00:00 by arangoni          #+#    #+#             */
/*   Updated: 2021/11/08 17:05:56 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int				m;
	unsigned long	i;

	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		i = len - 1;
		len = 0;
		m = -1;
	}
	else
	{
		i = 0;
		m = 1;
		len--;
	}
	while (i != len + m)
	{
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		i += m;
	}
	return (dst);
}
