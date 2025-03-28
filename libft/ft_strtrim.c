/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <ssadi-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:09:41 by ssadi-ou          #+#    #+#             */
/*   Updated: 2024/11/11 12:49:17 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkchar(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	debut;
	size_t	fin;
	size_t	i;
	char	*str;

	debut = 0;
	fin = ft_strlen(s1);
	i = 0;
	while (s1[debut] && ft_checkchar(s1[debut], set) == 1)
	{
		debut++;
	}
	while (fin > debut && ft_checkchar(s1[fin - 1], set))
	{
		fin--;
	}
	str = (char *)malloc(sizeof(*s1) * (fin - debut + 1));
	if (!str)
		return (NULL);
	while (debut < fin)
	{
		str[i++] = s1[debut++];
	}
	str[i] = 0;
	return (str);
}
