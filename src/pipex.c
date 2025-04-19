/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:32:21 by lflayeux          #+#    #+#             */
/*   Updated: 2025/04/16 15:13:21 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_1(char **argv, char **env, t_file_check *files, pid_t pid)
{
	if (pid == -1)
		error(2, NULL);
	if (pid == 0)
	{
		close(files->fd[0]);
		if (dup2(files->fd_in, STDIN_FILENO) == -1)
			error(2, argv[1]);
		dup2(files->fd[1], STDOUT_FILENO);
		close_fd(files);
		execute_cmd(argv[2], env, files);
	}
}

void	child_2(char **argv, char **env, t_file_check *files, pid_t pid)
{
	if (pid == -1)
		error(2, NULL);
	if (pid == 0)
	{
		close(files->fd[1]);
		check_fd_out(argv[4], files);
		if (dup2(files->fd_out, STDOUT_FILENO) == -1)
			error(2, argv[1]);
		dup2(files->fd[0], STDIN_FILENO);
		close_fd(files);
		execute_cmd(argv[3], env, files);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_file_check	files;
	pid_t			pid1;
	pid_t			pid2;

	if (argc != 5 || env[0] == NULL)
		error(1, NULL);
	init_fd(&files);
	check_fd_in(argv[1], &files);
	if (pipe(files.fd) == -1)
		error(2, NULL);
	pid1 = fork();
	child_1(argv, env, &files, pid1);
	pid2 = fork();
	child_2(argv, env, &files, pid2);
	close_fd(&files);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
