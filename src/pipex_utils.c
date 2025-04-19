/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:59:46 by lflayeux          #+#    #+#             */
/*   Updated: 2025/04/16 15:13:39 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int flag, char *argv)
{
	if (flag == 1)
	{
		ft_printf("USE ===> <file_in> <command> <command> <file_out>\n");
		exit(1);
	}
	if (flag == 2)
	{
		ft_printf("bash: %s: %s\n", argv, strerror(errno));
		exit(1);
	}
	if (flag == 3)
	{
		ft_printf("bash: %s: %s\n", argv, strerror(errno));
		return ;
	}
	if (flag == 4)
		exit(127);
	if (flag == 5)
	{
		ft_printf("bash: %s: %s\n", argv, strerror(errno));
		exit(1);
	}
}

char	*check_env(char **env)
{
	int		i;
	char	*env_line;

	i = 0;
	env_line = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			env_line = ft_strdup(env[i]);
			return (env_line);
		}
		i++;
	}
	if (env_line)
		free(env_line);
	return (NULL);
}

char	*get_path(char **cmd, char **env)
{
	char	*ev_line;
	char	*path;
	char	**path_dir;
	char	*cmd_dir;
	int		i;

	if (cmd == NULL || cmd[0] == NULL)
		return (NULL);
	ev_line = check_env(env);
	if (ev_line == NULL)
		return (NULL);
	path_dir = ft_split(&ev_line[5], ':');
	free(ev_line);
	i = 0;
	while (path_dir[i])
	{
		cmd_dir = ft_strjoin(path_dir[i++], "/");
		path = ft_strjoin(cmd_dir, cmd[0]);
		free(cmd_dir);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_tab((void **)path_dir), path);
		free(path);
	}
	ft_free_tab((void **)path_dir);
	return (NULL);
}

void	execute_cmd(char *argv, char **env, t_file_check *files)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (access(cmd[0], F_OK | X_OK) == 0)
	{
		if (execve(cmd[0], cmd, env) == -1)
		{
			ft_free_tab((void **)cmd);
			return (close_fd(files), error(3, argv));
		}
	}
	path = get_path(cmd, env);
	if (path == NULL)
		return (ft_free_tab((void **)cmd), close_fd(files), error(4, NULL));
	if (execve(path, cmd, env) == -1)
	{
		ft_free_tab((void **)cmd);
		free(path);
		return (close_fd(files), error(3, argv));
	}
}
