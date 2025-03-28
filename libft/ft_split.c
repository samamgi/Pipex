/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <ssadi-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:07:41 by ssadi-ou          #+#    #+#             */
/*   Updated: 2024/11/12 22:39:44 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlentab(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
		{
			i++;
		}
		if (s[i] && s[i] != c)
		{
			j++;
			while (s[i] && s[i] != c)
			{
				i++;
			}
		}
	}
	return (j);
}

static void	ft_fill(char const *src, char *d, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] && src[i] == c)
	{
		i++;
	}
	while (src[i] && src[i] != c)
	{
		d[j] = src[i];
		i++;
		j++;
	}
	d[j] = 0;
}

static void	ft_set(char **tab, char const *s, char c)
{
	size_t	i;
	size_t	co;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		co = 0;
		while (s[i + co] && s[i + co] != c)
			co++;
		if (co > 0)
		{
			tab[j] = (char *)malloc(sizeof(char) * (co + 1));
			if (!tab[j])
				return ;
			ft_fill((s + i), tab[j], c);
			j++;
			i += co;
		}
		else
			i++;
	}
	tab[j] = 0;
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**split;

	words = ft_strlentab(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	ft_set(split, s, c);
	return (split);
}
