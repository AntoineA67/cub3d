/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:16:32 by arangoni          #+#    #+#             */
/*   Updated: 2022/05/11 12:30:31 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_dtoa(double n)
{
	char	*inte;
	char	*dec;
	char	*res;

	inte = ft_itoa((int)n);
	dec = ft_itoa((int)((n - (int)n) * 100));
	res = ft_strjoin(inte, ".");
	free(inte);
	inte = ft_strjoin(res, dec);
	free(res);
	free(dec);
	return (inte);
}
