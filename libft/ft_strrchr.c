/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:33:26 by arangoni          #+#    #+#             */
/*   Updated: 2021/11/08 12:20:03 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len_s;
	char	*p;

	len_s = ft_strlen(s);
	p = (char *)s;
	if (c == 0)
		return (p + len_s);
	while (len_s--)
		if (p[len_s] == (char)c)
			return (p + len_s);
	return (NULL);
}
