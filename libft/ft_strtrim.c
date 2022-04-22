/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:01:22 by arangoni          #+#    #+#             */
/*   Updated: 2021/11/08 17:15:09 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	size_t			len;

	if (!set)
		return (ft_strdup(s1));
	if (!s1)
		return (NULL);
	start = 0;
	len = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (len > 0 && ft_strchr(set, s1[len - 1]))
		len--;
	return (ft_substr(s1, start, len - start));
}
