/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 05:25:10 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/03/31 05:25:28 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	check_exist(char *cmd)
{
	if ((access(cmd, F_OK) == -1) || !cmd || (cmd && ft_strlen(cmd) <= 0))
	{
		put_error(cmd, 1, NULL);
		return (-1);
	}
	else if ((access(cmd, F_OK) == 0) && (access(cmd, X_OK) == 0))
		return (1);
	else
	{
		put_error(cmd, 2, NULL);
		return (-1);
	}
}

void	freeall(char *slash, char *path, char **split_path, char **argv)
{
	int	i;

	i = 0;
	if (slash)
		free(slash);
	if (path)
		free(path);
	if (split_path)
	{
		while (split_path[i])
		{
			free(split_path[i]);
			i++;
		}
		free(split_path);
	}
	if (argv)
	{
		while (argv[i])
		{
			free(argv[i]);
			i++;
		}
		free(argv);
	}
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

void	put_error(char *path, int error, char **argv)
{
	if (error == 1)
	{
		ft_putstr_fd("command not found: ", 2);
		if (argv)
		{
			ft_putendl_fd(argv[0], 2);
			freeall(NULL, NULL, NULL, argv);
		}
		else
			ft_putendl_fd(path, 2);
		exit(127);
	}
	if (error == 2)
	{
		ft_putstr_fd("Permission denied: ", 2);
		if (argv)
		{
			ft_putendl_fd(argv[0], 2);
			freeall(NULL, NULL, NULL, argv);
		}
		else
			ft_putendl_fd(path, 2);
		exit(126);
	}
}

char	*pathfinder(char *slash, char **split_path)
{
	int		i;
	char	*path;

	path = NULL;
	i = 0;
	while (split_path[i])
	{
		path = ft_strjoin(split_path[i], slash);
		if (!path)
			return (free(path), NULL);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
