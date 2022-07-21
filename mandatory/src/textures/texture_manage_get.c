/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manage_get.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:46:15 by qroussea          #+#    #+#             */
/*   Updated: 2022/07/21 15:48:11 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_data	*get_texture(t_vars	*vars, char	*name, int nb)
{
	t_textures	*act;
	int			i;

	act = vars->textures;
	while (act && ft_strncmp(act->name, name, ft_strlen(name)) && act->next)
		act = act->next;
	if (!ft_strncmp(act->name, name, ft_strlen(name)))
	{
		i = 0;
		while (i < nb && (act->imgtab[i] != NULL))
			i++;
		return (act->imgtab[i]);
	}
	printf("NOT FOUND:%s\n", name);
	exit_err(vars, 1, "Invalid texture");
	return (NULL);
}

int	get_animsize(t_vars	*vars, char *name)
{
	t_textures	*act;
	int			i;

	act = vars->textures;
	while (act && ft_strncmp(act->name, name, ft_strlen(name)) && act->next)
		act = act->next;
	if (act && !ft_strncmp(act->name, name, ft_strlen(name)))
	{
		i = 0;
		while (act->imgtab[i] != NULL)
			i++;
		return (i);
	}
	return (0);
}
