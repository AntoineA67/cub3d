/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:51:09 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/11 13:03:59 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strschr(char *s, char *finds)
{
	int		i;

	i = 0;
	if (!s)
		return (-1);
	while (finds && finds[i])
	{
		if (ft_strchr(s, finds[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	str_to_rgb(t_rgb *col, char *str)
{
	char	**splitted;
	int		i;

	splitted = ft_split(str, ',');
	i = -1;
	while (splitted[++i])
		;
	col->r = ft_atoi(splitted[0]);
	col->g = ft_atoi(splitted[1]);
	col->b = ft_atoi(splitted[2]);
	ft_freetab(splitted);
	return (0);
}

int	err_format_rgb(char *str)
{
	char	*cpy;
	int		i;

	cpy = ft_strtrim(str, " ");
	if (!cpy)
		return (1);
	i = -1;
	while (cpy[++i])
		if (!ft_isdigit(cpy[i]))
			return (1);
	free(cpy);
	return (0);
}
