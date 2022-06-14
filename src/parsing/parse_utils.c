/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:51:09 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/14 11:42:45 by arangoni         ###   ########.fr       */
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
	if (i > 3)
		return (1);
	free(cpy);
	return (0);
}

static char **check_n_comma(char *str)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	if (str[ft_strlen(str) - 1] == '\n')
		str[ft_strlen(str) - 1] = '\0';
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

	splitted = check_n_comma(str);
	if (!splitted)
		exit_err(vars, 1);
	i = -1;
	while (splitted[++i])
		if (err_format_rgb(splitted[i]))
			exit_err(vars, 1);
	if (i > 3)
		exit_err(vars, 1);
	col->r = ft_atoi(splitted[0]);
	col->g = ft_atoi(splitted[1]);
	col->b = ft_atoi(splitted[2]);
	if (col->r > 255 || col->g > 255 || col->b > 255)
		exit_err(vars, 1);
	ft_freetab(splitted);
	return (0);
}
