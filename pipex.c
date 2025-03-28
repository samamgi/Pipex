/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:54:49 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/03/26 05:40:43 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void    freesplit(char **split)
{
        int     i;

        i = 0;
        while (split[i])
        {
                free(split[i]);
                i++;
        }
        free(split);
}

char    *getpath(char **env)
{
        int     i;

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

int    commande(char *cmd, char **env)
{
        char    *path;
        char    *slash;
        char    **split_path;
        char    **argv;
        int     i;

        argv = ft_split(cmd, ' ');
        path = getpath(env);
        slash = ft_strjoin("/", argv[0]);
        split_path = ft_split(path, ':');
        if (!split_path)
        {
                freesplit(split_path);
                return (-1);
        }
        path = NULL;
        i = 0;
        while (split_path[i])
        {
                path = ft_strjoin(split_path[i], slash);
                if (access(path, F_OK) == 0)
                { execve(path, argv, env);
                        free(slash);
                        free(path);
                        freesplit(split_path);
                        freesplit(argv);
                        return (1);
                }
                free(path);
                i++;
        }
        free(slash);
        free(path);
        freesplit(split_path);
        freesplit(argv);
        ft_putstr_fd("command not found\n", 2);
        return (-1);
}

int    check_commande(char *cmd, char **env)
{
        char    *path;
        char    *slash;
        char    **split_path;
        char    **argv;
        int     i;

        if (!cmd || (cmd && ft_strlen(cmd) <= 0))
        {
                //free(cmd);
                //freesplit(env);
                //ft_putstr_fd("command not found\n", 2);
                return (-1);
        }
        argv = ft_split(cmd, ' ');
        path = getpath(env);
        slash = ft_strjoin("/", argv[0]);
        split_path = ft_split(path, ':');
        if (!split_path)
        {
                free(slash);
                free(path);
                freesplit(split_path);
                freesplit(argv);
                return (-1);
        }
        path = NULL;
        i = 0;
        while (split_path[i])
        {
                path = ft_strjoin(split_path[i], slash);
                if (access(path, F_OK) == 0)
                {
                        free(slash);
                        free(path);
                        freesplit(split_path);
                        freesplit(argv);
                        return (1);
                }
                free(path);
                i++;
        }
        //path = ft_strjoin("command not found: ", argv[0]);
        //ft_putstr_fd(path, 2);
        //ft_putchar_fd('\n', 2);
        free(slash);
        //free(path);
        freesplit(split_path);
	freesplit(argv);
        return (-1);
}


int     main(int ac, char **av, char **env)
{
        int     fd1;
        int     fd2;
        int     pipefd[2];
        int     pid1;
        int     pid2;
        char    *err;

	if (ac == 5)
        {
		if (access(av[1], F_OK) == -1)
		{
			err = ft_strjoin(av[1], ": No such file or directory\n");
                        ft_putstr_fd(err, 2);
                        free(err);
                }
		if (av[1] && (access(av[1], R_OK) == -1) && (ft_strlen(av[1]) > 0))
		{
			err = ft_strjoin(av[1], ": Permissions Denied\n");
                        ft_putstr_fd(err, 2);
                        return (free(err), -1);
		}
                if ((check_commande(av[2], env) == - 1) || (check_commande(av[3], env) == -1))
                {
                        if (check_commande(av[2], env) == -1)
                        {
                                err = ft_strjoin("Command not found: ", av[2]);
                                ft_putstr_fd(err, 2);
                                ft_putchar_fd('\n', 2);
                                free(err);
                        }
                        if (check_commande(av[3], env) == -1)
                        {
                                err = ft_strjoin("Command not found: ", av[3]);
                                ft_putstr_fd(err, 2);
                                ft_putchar_fd('\n', 2);
                                free(err);
                        }
                        return (-1);
                }
		if ((access(av[ac - 1], F_OK) == 0) && (access(av[ac - 1], W_OK) == -1))
		{
	               err = ft_strjoin(av[ac - 1], ": Permissions Denied\n");
                       ft_putstr_fd(err, 2);
                       return (free(err), -1);
		}
		if (av[ac - 1] && (ft_strlen(av[ac - 1]) == 0))
		{
                        err = ft_strjoin(av[ac - 1], ": No such file or directory\n");
                        ft_putstr_fd(err, 2);
                        return (free(err), -1);
                }
		fd1 = open(av[1], O_RDONLY, 0644);
                fd2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd2 == -1)
                {
		       err = ft_strjoin(av[ac - 1], ": Permissions Denied\n");
		       ft_putstr_fd(err, 2);
		       free(err);
                } 
		pipe(pipefd);
                pid1 = fork();
                if (pid1 == 0)
                {
			close(pipefd[0]);
			if (fd1 == -1)
			{
				close(pipefd[1]);
				exit(1);
			}
                        if (dup2(fd1, 0) == -1)
			{
				close(fd1);
				exit(EXIT_FAILURE);
			}
                        if (dup2(pipefd[1], 1) == -1)
			{
				close(pipefd[1]);
				exit(EXIT_FAILURE);
			}
			close(pipefd[1]);
			commande(av[2], env);
                }
                pid2 = fork();
                if (pid2 == 0)
                {
                        close(pipefd[1]);
			if (fd2 == -1)
			{
				close(pipefd[0]);
				exit(EXIT_FAILURE);
			}
			printf("check");
			if (dup2(fd2, 1) == -1)
			{
				close(fd2);
				exit(EXIT_FAILURE);
			}
			close(fd2);
                        if (dup2(pipefd[0], 0) == -1)
			{
				close(pipefd[0]);
				exit(EXIT_FAILURE);
			}
			close(pipefd[0]);
			commande(av[3], env);
                }
                close(pipefd[1]);
                close(pipefd[0]);
		if (fd1 != -1)
		{
                	wait(NULL);
		}
			wait(NULL);
        }
        return (0);
}
