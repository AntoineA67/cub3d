/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:01:47 by arangoni          #+#    #+#             */
/*   Updated: 2021/11/04 17:49:41 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while ((i < n) && (t1[i] == t2[i]))
		i++;
	if (i == n)
		return (t1[i - 1] - t2[i - 1]);
	return (t1[i] - t2[i]);
}
