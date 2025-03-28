/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <ssadi-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:31:04 by ssadi-ou          #+#    #+#             */
/*   Updated: 2024/11/12 22:31:05 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		nbr = -nbr;
		ft_putchar_fd('-', fd);
	}
	if (nbr > 9)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putnbr_fd(nbr % 10, fd);
	}
	else
		ft_putchar_fd(nbr + 48, fd);
}
