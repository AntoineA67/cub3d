/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:50:44 by arangoni          #+#    #+#             */
/*   Updated: 2021/11/08 17:14:10 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*t;
	int		i;
	int		len_s1;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	t = (char *)malloc((len_s1 + ft_strlen(s2) + 1) * sizeof(char));
	if (!t)
		return (NULL);
	i = -1;
	while (++i < len_s1)
		t[i] = s1[i];
	i = -1;
	while (s2[++i])
		t[len_s1 + i] = s2[i];
	t[len_s1 + i] = '\0';
	return (t);
}
