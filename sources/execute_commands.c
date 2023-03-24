/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_commands.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 15:33:53 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/03/24 14:07:37 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*combine_command_path(char *path, char *cmd)
{
	char	*command_path;
	size_t	malloc_len;

	malloc_len = ft_strlen(path) + ft_strlen("/") + ft_strlen(cmd) + 1;
	command_path = malloc(malloc_len * sizeof(char));
	if (command_path == NULL)
		return (NULL);
	ft_strlcpy(command_path, path, malloc_len);
	ft_strlcat(command_path, "/", malloc_len);
	ft_strlcat(command_path, cmd, malloc_len);
	return (command_path);
}

static void	execute_command(char **envp, char **paths, t_command *command)
{
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		if (command->executable_location != NULL)
			free(command->executable_location);
		command->executable_location
			= combine_command_path(paths[i], command->argv[0]);
		execve(command->executable_location, command->argv, envp);
		i++;
	}
	// todo: try to execute the command from local directory
	exit(EXIT_FAILURE);  // todo catch error!
}

static int	set_filedescriptors(t_data *data, size_t i_command)
{
	if (i_command == 0)
	{
		if (dup2(data->fd_infile, STDIN_FILENO) == -1)
			return (-1);
	}
	else
	{
		if (dup2(data->pipes[i_command - 1][0], STDIN_FILENO) == -1)
			return (-1);
	}
	if (i_command + 1 == data->nr_commands)
	{
		if (dup2(data->fd_outfile, STDOUT_FILENO) == -1)
			return (-1);
	}
	else
	{
		if (dup2(data->pipes[i_command][1], STDOUT_FILENO) == -1)
			return (-1);
	}
	return (1);
}

int	execute_commands_in_child_processes(char **envp, t_data *data)
{
	pid_t	new_pid;
	size_t	i;

	i = 0;
	while (i < data->nr_commands)
	{
		new_pid = fork();
		if (new_pid == -1)
			return (-1);
		if (new_pid == 0)
		{
			if (set_filedescriptors(data, i) < 0)
				return (-1);
			if (close_pipes_before_running_command_i(data, i) < 0)
				return (-1);
			execute_command(envp, data->paths, data->commands[i]);
		}
		i++;
	}
	if (close_all_pipes(data) < 0)
		return (-1);
	i = 0;
	while (i < data->nr_commands)
	{
		if (wait(NULL) == -1)
			return (-1);
		i++;
	}
	return (1);
}
