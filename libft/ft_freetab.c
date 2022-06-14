/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 02:36:47 by arangoni          #+#    #+#             */
/*   Updated: 2022/06/13 16:28:42 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freetab(void *splitted)
{
	int		i;
	char	**split;

	split = (char **)splitted;
	if (!split)
		return ;
	i = -1;
	while (split[++i])
		free(split[i]);
	split[i];
	free(split);
}
