/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 02:36:47 by arangoni          #+#    #+#             */
/*   Updated: 2022/02/03 00:24:13 by arangoni         ###   ########.fr       */
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
	free(split);
}
