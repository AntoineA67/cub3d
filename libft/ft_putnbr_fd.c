/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arangoni <arangoni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:09:09 by arangoni          #+#    #+#             */
/*   Updated: 2021/11/07 17:25:47 by arangoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	m;

	m = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		m = -m;
	}
	if (m >= 10)
		ft_putnbr_fd(m / 10, fd);
	ft_putchar_fd(m % 10 + '0', fd);
}
