/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_memset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:28:53 by arangoni          #+#    #+#             */
/*   Updated: 2022/01/25 18:51:00 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_int_memset(void *b, int c, size_t len)
{
	size_t	i;
	int		*ptr;

	ptr = b;
	i = -1;
	while (++i < len)
		ptr[i] = c;
	return (b);
}
