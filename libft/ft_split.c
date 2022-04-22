/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:26:27 by arangoni          #+#    #+#             */
/*   Updated: 2021/11/09 17:16:38 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(const char *s, char c)
{
	int	i;
	int	w;

	w = 0;
	i = 0;
	while (*s)
	{
		i = 0;
		while (s[i] && s[i] != c)
			i++;
		if (i != 0)
			w++;
		while (s[i] && s[i] == c)
			i++;
		s += i;
	}
	return (w);
}

static void	*free_tab(char **tab, int w)
{
	int	i;

	i = -1;
	while (++i < w)
		free(tab[i]);
	free(tab);
	return (NULL);
}

static char	**fill_tab(const char *s, char **tab, char c)
{
	int		i;
	int		w;

	w = 0;
	while (*s)
	{
		i = 0;
		while (s[i] != c && s[i])
			i++;
		tab[w] = ft_substr(s, 0, i);
		if (!tab[w++])
			return (free_tab(tab, w));
		while (s[i] == c && s[i])
			i++;
		s += i;
	}
	tab[w] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char		**tab;

	if (!s)
		return (NULL);
	while (*s && *s == c)
		s++;
	tab = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	return (fill_tab(s, tab, c));
}
