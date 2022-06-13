/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manage_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:24:14 by qroussea          #+#    #+#             */
/*   Updated: 2022/06/10 14:30:38 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	freeframes(t_data	**datas)
{
	int	i;

	i = 0;
	while (datas[0] != NULL)
	{
		i = 0;
		while (datas[i] != NULL)
			i++;
		if (i)
		{
			free(datas[i - 1]);
			datas[i - 1] = NULL;
		}
		else
			free(datas[0]);
	}
	free(datas);
}

void	free_textures(t_vars *vars)
{
	t_textures	*act;
	t_textures	*last;

	while (vars->textures)
	{
		last = NULL;
		act = vars->textures;
		while (act->next)
		{
			last = act;
			act = act->next;
		}
		freeframes(act->imgtab);
		act->imgtab = NULL;
		free(act);
		if (last)
			last->next = NULL;
		else
			vars->textures = NULL;
	}
}
