/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <ssadi-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:58:29 by ssadi-ou          #+#    #+#             */
/*   Updated: 2024/11/13 15:36:30 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s);

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	lend;
	size_t	lens;

	lend = ft_strlen(dest);
	lens = ft_strlen(src);
	j = 0;
	if (size == 0)
	{
		return (lens);
	}
	if (size <= lend)
	{
		return (lens + size);
	}
	i = lend;
	while (src[j] && (i + j + 1 < size))
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = 0;
	return (i + lens);
}
