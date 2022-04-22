/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:49:04 by arangoni          #+#    #+#             */
/*   Updated: 2021/11/08 17:10:58 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*t;
	int		i;

	if (!s)
		return (NULL);
	i = -1;
	t = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!t)
		return (NULL);
	while (s[++i])
		t[i] = f(i, s[i]);
	t[i] = '\0';
	return (t);
}
