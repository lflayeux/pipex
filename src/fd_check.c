/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:14:05 by lflayeux          #+#    #+#             */
/*   Updated: 2025/04/15 15:36:28 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_fd_in(char *argv, t_file_check *files)
{
	if (argv == NULL)
		error(2, argv);
	files->fd_in = open(argv, O_RDONLY);
	if (files->fd_in == -1)
		error(3, argv);
}

void	check_fd_out(char *argv, t_file_check *files)
{
	if (argv == NULL)
		error(2, argv);
	files->fd_out = open(argv, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (files->fd_out == -1)
		error(2, argv);
}

void	close_fd(t_file_check *files)
{
	if (files->fd_in != 999)
		close(files->fd_in);
	if (files->fd_out != 999)
		close(files->fd_out);
	if (files->fd[0] != 999)
		close(files->fd[0]);
	if (files->fd[1] != 999)
		close(files->fd[1]);
}

void	init_fd(t_file_check *files)
{
	files->fd_in = 999;
	files->fd_out = 999;
	files->fd[0] = 999;
	files->fd[1] = 999;
}
