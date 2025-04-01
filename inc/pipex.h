/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 05:30:15 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/04/02 01:10:33 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

int		check_exist(char *cmd);

char	*getpath(char **env);

void	put_error(char *path, int error, char **argv);

char	*pathfinder(char *slash, char **split_path);

void	commande(char *cmd, char **env);

void	execlast(char *slash, char **split_path, char **argv, char **env);

int		execslash(char *cmd, char *path, char **env);

void	freeall(char *slash, char *path, char **split_path, char **argv);

#endif
