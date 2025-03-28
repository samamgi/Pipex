/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <ssadi-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 01:55:39 by ssadi-ou          #+#    #+#             */
/*   Updated: 2024/11/13 20:04:37 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ar;
	size_t			i;

	i = 0;
	if (size)
	{
		if (nmemb > SIZE_MAX / size)
			return (NULL);
	}
	ar = (unsigned char *)malloc(nmemb * size);
	if (!ar)
		return (NULL);
	while (i < nmemb * size)
	{
		ar[i] = 0;
		i++;
	}
	return ((void *)ar);
}
