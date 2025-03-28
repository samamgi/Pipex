/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 22:38:56 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/03/18 00:33:55 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "./libft/libft.h"

void    freesplit(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*getpath(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (&env[i][5]);
		i++;
	}
	return (NULL);
}

void    commande(char *cmd, char **env)
{
        char    *path;
	char	*slash;
        char    **split_path;
        char    **argv;
	int	i;

	if (!cmd)
	{
		ft_putstr_fd("command not found\n", 2);
		return;
	}
        argv = ft_split(cmd, ' ');
	if (!argv)
	{
		ft_putstr_fd("command not found\n", 2);
		free(argv);
		return;
	}
	path = getpath(env);
	if (!path)
	{
		ft_putstr_fd("permissions denied\n", 2);
		free(argv);
		return;
	}
	slash = ft_strjoin("/", argv[0]);
	split_path = ft_split(path, ':');
	path = NULL;
	i = 0;
	while (split_path[i])
	{
		path = ft_strjoin(split_path[i], slash);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
		if (access(path, F_OK) == 0)
		{
			execve(path, argv, env);
			break;
		}
		i++;
	}
        ft_putstr_fd("command not found\n", 2);
}

int	main(int ac, char **av, char **env)
{
	if (ac == 2)
	{
		//ft_putstr_fd(getpath(env), 2);
		//ft_putchar_fd('\n', 2);
		(void)getpath;
		commande(av[1], env);
	}
	return (0);
}
