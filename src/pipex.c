/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:54:49 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/04/02 00:52:18 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	child1(int fd1, int pipefd[2], char **av, char **env)
{
	close(pipefd[0]);
	fd1 = open(av[1], O_RDONLY, 0644);
	if (fd1 == -1)
	{
		close(pipefd[1]);
		perror(av[1]);
		exit(1);
	}
	if (dup2(fd1, STDIN_FILENO) == -1)
	{
		close(fd1);
		exit(EXIT_FAILURE);
	}
	close(fd1);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	commande(av[2], env);
}

static void	child2(int fd2, int pipefd[2], char **av, char **env)
{
	close(pipefd[1]);
	fd2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 == -1)
	{
		close(pipefd[0]);
		perror(av[4]);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd2, STDOUT_FILENO) == -1)
	{
		close(fd2);
		exit(EXIT_FAILURE);
	}
	close(fd2);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		close(pipefd[0]);
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	commande(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		fd1;
	int		fd2;
	int		pipefd[2];
	pid_t	pid;

	if ((ac != 5) || (pipe(pipefd) == -1))
		return (1);
	fd1 = -1;
	fd2 = -1;
	pid = fork();
	if (pid == 0)
		child1(fd1, pipefd, av, env);
	if (pid == -1)
		return (close(pipefd[0]), close(pipefd[1]), -1);
	pid = fork();
	if (pid == 0)
		child2(fd2, pipefd, av, env);
	if (pid == -1)
		return (close(pipefd[0]), close(pipefd[1]), -1);
	close(pipefd[1]);
	close(pipefd[0]);
	if (fd1 == -1)
		wait(NULL);
	wait(NULL);
	return (0);
}
