/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:16:32 by arangoni          #+#    #+#             */
/*   Updated: 2021/11/08 17:10:43 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_n(int n)
{
	int	i;

	i = 1;
	while (n >= 10 || n <= -10)
	{
		i++;
		n /= 10;
	}
	if (n < 0)
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	int			i;
	long int	m;
	char		*s;

	i = size_n(n);
	s = (char *)malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	m = n;
	if (n < 0)
	{
		s[0] = '-';
		m = -m;
	}
	s[i] = '\0';
	while (m >= 10 || m <= -10)
	{
		s[i - 1] = m % 10 + '0';
		i--;
		m /= 10;
	}
	s[i - 1] = m + '0';
	return (s);
}
