/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:36:04 by arangoni          #+#    #+#             */
/*   Updated: 2021/11/08 17:07:32 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*t;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < (size_t)start)
		len = 0;
	if (len != 0 && ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	t = (char *)malloc((len + 1) * sizeof(char));
	if (!t)
		return (NULL);
	i = 0;
	while (i < len && s[(size_t)start + i])
	{
		t[i] = s[(size_t)start + i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
