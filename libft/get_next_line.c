/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:26:24 by arangoni          #+#    #+#             */
/*   Updated: 2022/02/02 22:30:30 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_freejoin(char *s1, char const *s2)
{
	char	*t;
	int		i;
	int		len_s1;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	t = (char *)malloc((len_s1 + ft_strlen(s2) + 1) * sizeof(char));
	if (!t)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	while (++i < len_s1)
		t[i] = s1[i];
	i = -1;
	while (s2[++i])
		t[len_s1 + i] = s2[i];
	t[len_s1 + i] = '\0';
	free(s1);
	return (t);
}

static char	*found_n(char **cat, char *s, char *buf)
{
	char			*t;
	size_t			len_cat;

	len_cat = ft_strlen(*cat);
	t = (char *)malloc((len_cat + s - buf + 2) * sizeof(char));
	if (!t)
		return (NULL);
	ft_memmove(t, *cat, len_cat);
	ft_memmove(t + len_cat, buf, s - buf + 1);
	t[len_cat + s - buf + 1] = '\0';
	if (*cat)
		free(*cat);
	ft_memmove(buf, s + 1, ft_strlen(s));
	return (t);
}

static int	read_next(int fd, char *buf, char **cat)
{
	int		read_size;

	*cat = ft_freejoin(*cat, buf);
	if (!*cat)
		return (-1);
	read_size = read(fd, buf, BUFFER_SIZE);
	if (read_size == -1)
	{
		free(*cat);
		return (-1);
	}
	buf[read_size] = '\0';
	if (!read_size)
	{
		if (**cat)
			return (0);
		free(*cat);
		return (-1);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char		buf[OPEN_MAX][BUFFER_SIZE + 1];
	char			*cat;
	char			*s;
	int				read_size;

	if (fd > OPEN_MAX || fd < 0)
		return (NULL);
	cat = ft_strdup("");
	if (!cat)
		return (NULL);
	s = buf[fd];
	while (*s != '\n')
	{
		if (!*s)
		{
			read_size = read_next(fd, buf[fd], &cat);
			if (read_size == -1)
				return (NULL);
			else if (read_size == 0)
				return (cat);
			s = buf[fd] - 1;
		}
		s++;
	}
	return (found_n(&cat, s, buf[fd]));
}
