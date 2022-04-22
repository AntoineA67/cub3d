/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:16:21 by arangoni          #+#    #+#             */
/*   Updated: 2021/11/03 17:20:53 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	src_len;
	unsigned int	dst_len;
	unsigned int	i;
	unsigned int	dist;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = 0;
	while (i < dstsize && dst[i])
		i++;
	dist = i;
	if (dstsize < dst_len || dstsize == 0)
		return (src_len + dstsize);
	if (dst_len < dstsize)
	{
		i = 0;
		while ((i < dstsize - dst_len - 1) && src[i])
		{
			dst[dst_len + i] = src[i];
			i++;
		}
	}
	if (i > 0)
		dst[dst_len + i] = '\0';
	return ((size_t)(src_len + dist));
}
