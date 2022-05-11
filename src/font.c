/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:07:51 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/11 11:09:11 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	img_text(t_vars *vars, char *str, t_coord p)
{
	int	i;
	int	j;
	int	k;
	int	scale;

	scale = p.z;
	if (!scale)
		return ;
	i = -1;
	j = 0;
	while (str[++i])
	{
		j = -1;
		while (++j < 8 * scale)
		{
			k = -1;
			while (++k < 8 * scale)
			{
				if ((vars->font[(int)str[i]]>>(64 - (j / scale * 8) - (k / scale))) & 1)
					pixel_put(vars->img, p.x + k + i * (8 * scale), p.y + j, to_rgb(p.c, 0));
			}	
		}
	}
}

void	affect_ascii(t_vars *vars)
{
	int			i;
	char		*line;
	int			fd;

	fd = open("./fonts/font.csv", O_RDONLY);
	if (fd < 0)
	{
		write(2, "Font not found\n", 16);
		return ;
	}
	i = -1;
	while (++i < 128)
	{
		line = get_next_line(fd);
		if (!line || ft_strlen(line) < 3)
		{
			write(2, "Error while parsing fonts\n", 16);
			return ;
		}	
		vars->font[i] = ft_atoi_base_u_64(line + 2, "0123456789ABCDEF");
	}
}
