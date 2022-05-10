/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:07:51 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/10 19:01:27 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	img_text(t_vars *vars, char *str, t_coord p)
{
	int	i;
	int	j;
	int	scale;

	scale = p.z;
	if (!scale)
		return ;
	i = -1;
	j = 0;
	while (str[++i])
	{
		j = -1;
		while (++j < 64 * scale * scale)// && is_in_window(vars, p.x + j % 8 + i * 8, p.y + j / 8))
		{
			// printf("%d %d\t", p.x + j % (8 * scale) + i * (8 * scale), p.y + j / (8 * scale));
			if ((vars->font[(int)str[i]]>>(64 - ((j / scale) - (((j / (8 * scale)) % scale) * 8) - (8 * ((j / (8 * scale)) / scale))))) & 1)
				pixel_put(vars->img, p.x + j % (8 * scale) + i * (8 * scale), p.y + j / (8 * scale), to_rgb(p.c, 0));
			// printf("%d ", (j / scale) - ((j / (8 * scale)) / scale));
			printf("%d ", ((j / scale) - (((j / (8 * scale)) % scale) * 8) - (8 * ((j / (8 * scale)) / scale))));	
		}
		printf("\n%d %d\n\n", j, j / scale);
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
		printf("%llu\n", vars->font[i]);
	}
}
