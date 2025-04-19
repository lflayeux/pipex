/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:55:11 by lflayeux          #+#    #+#             */
/*   Updated: 2025/04/15 15:36:01 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

typedef struct s_file_check
{
	int		fd_in;
	int		fd_out;
	int		fd[2];
}		t_file_check;

// PIPEX
void	child_1(char **argv, char **env, t_file_check *files, pid_t pid);
void	child_2(char **argv, char **env, t_file_check *files, pid_t pid);

// PIPEX_UTILS
void	error(int flag, char *argv);
char	*check_env(char **env);
char	*get_path(char **cmd, char **env);
void	execute_cmd(char *argv, char **env, t_file_check *files);

// FD_CHECK
void	check_fd_in(char *argv, t_file_check *files);
void	check_fd_out(char *argv, t_file_check *files);
void	close_fd(t_file_check *files);
void	init_fd(t_file_check *files);

#endif
