/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:51:09 by qroussea          #+#    #+#             */
/*   Updated: 2022/07/28 16:21:38 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strnschr(char *s, char *finds)
{
	int		i;
	int		j;

	i = 0;
	if (!s || !finds)
		return (0);
	while (s && s[i])
	{
		j = 0;
		while (finds[j])
		{
			if (s[i] == finds[j])
				break ;
			j++;
		}
		if (j == (int)ft_strlen(finds))
			return (0);
		i++;
	}
	return (1);
}

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

int	err_format_rgb(char *str)
{
	char	*cpy;
	int		i;

	cpy = ft_strtrim(str, " ");
	if (!cpy)
	{
		free(cpy);
		return (1);
	}
	i = -1;
	while (cpy[++i])
	{
		if (!ft_isdigit(cpy[i]))
		{
			free(cpy);
			return (1);
		}
	}
	if (i > 3)
	{
		free(cpy);
		return (1);
	}
	free(cpy);
	return (0);
}

static char	**check_n_comma(char *str)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (str[++i])
		if (str[i] == ',')
			n++;
	if (n > 2)
		return (NULL);
	return (ft_split(str, ','));
}

int	str_to_rgb(t_vars *vars, t_rgb *col, char *str)
{
	char	**splitted;
	int		i;

	splitted = check_n_comma(str + 2);
	if (!splitted)
		exit_err_rgb(vars, splitted, str);
	i = -1;
	while (splitted[++i])
		if (err_format_rgb(splitted[i]))
			exit_err_rgb(vars, splitted, str);
	if (i > 3)
		exit_err_rgb(vars, splitted, str);
	col->r = ft_atoi(splitted[0]);
	col->g = ft_atoi(splitted[1]);
	col->b = ft_atoi(splitted[2]);
	col->v = 1;
	if (col->r > 255 || col->g > 255 || col->b > 255)
		exit_err_rgb(vars, splitted, str);
	ft_freetab(splitted);
	return (0);
}
