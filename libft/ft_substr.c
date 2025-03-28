/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <ssadi-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 07:40:51 by ssadi-ou          #+#    #+#             */
/*   Updated: 2024/11/11 12:14:46 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strnull(void)
{
	char	*snull;

	snull = malloc(1);
	if (!snull)
		return (NULL);
	snull[0] = 0;
	return (snull);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		n;
	char		*str;

	if (!s)
	{
		return (NULL);
	}
	n = ft_strlen(s);
	if (start > (unsigned int)n)
	{
		return (ft_strnull());
	}
	if (len > n - start)
		len = n - start;
	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
	{
		return (NULL);
	}
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
