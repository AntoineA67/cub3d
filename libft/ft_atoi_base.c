/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 03:06:29 by arangoni          #+#    #+#             */
/*   Updated: 2022/01/24 03:06:52 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	c_str(unsigned char c, char *str, int v)
{
	int	i;
	int	n;

	if (!str)
		return (-1);
	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == c)
			n += 1;
		if (n == v)
			return (i);
		i++;
	}
	return (-1);
}

static int	check_error(char *base)
{
	int	i;

	if (!base)
		return (1);
	i = -1;
	while (base[++i] != '\0')
		if (base[i] == '+' || base[i] == '-' || (c_str(base[i], base, 2) > 0)
			|| base[i] == ' ' || (base[i] >= 9 && base[i] <= 13))
			return (1);
	if (i < 2)
		return (1);
	return (0);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	mi;
	int	n;
	int	l_base;

	i = 0;
	mi = 1;
	n = 0;
	l_base = ft_strlen(base);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			mi *= -1;
	}
	if (check_error(base))
		return (0);
	while (c_str(str[i], base, 1) >= 0)
		n = l_base * n + c_str(str[i++], base, 1);
	return (mi * n);
}
