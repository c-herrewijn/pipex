/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_commands.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 15:33:53 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/04/07 17:07:13 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute_command_local_dir(char **envp, char **paths,
	t_command *command)
{
	if (command->executable_location != NULL)
		free(command->executable_location);
	command->executable_location = ft_strdup(command->argv[0]);
	if (command->executable_location != NULL)
		execve(command->executable_location, command->argv, envp);
	exit_with_error(command, paths);
}

static void	execute_command_from_path(char **envp, char **paths,
	t_command *command)
{
	int	i;

	i = 0;
	command->executable_location = NULL;
	while (paths[i] != NULL)
	{
		if (command->executable_location != NULL)
			free(command->executable_location);
		command->executable_location
			= combine_command_path(paths[i], command->argv[0]);
		if (command->executable_location == NULL)
			exit_with_error(command, paths);
		execve(command->executable_location, command->argv, envp);
		i++;
	}
	if (errno != EACCES)
		execute_command_local_dir(envp, paths, command);
	else
		exit_with_error(command, paths);
}

static void	run_child_process_and_exit(char **envp, t_data *data, size_t com_i)
{
	if (close_pipes_before_running_command_i(data, com_i) < 0)
		exit(1);
	if (set_filedescriptors(data, com_i) < 0)
		exit(1);
	if (data->paths != NULL)
		execute_command_from_path(envp, data->paths, data->commands[com_i]);
	else
		execute_command_local_dir(envp, data->paths, data->commands[com_i]);
}

int	wait_for_child_processes(t_data *data)
{
	size_t	i;
	pid_t	return_pid;
	int		stat_loc;

	i = 0;
	while (i < data->nr_commands)
	{
		return_pid = waitpid(data->commands[i]->pid, &stat_loc, 0);
		if (return_pid == -1)
		{
			perror(NULL);
			return (-1);
		}
		data->commands[i]->exit_status = WEXITSTATUS(stat_loc);
		i++;
	}
	return (0);
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
		{
			perror(NULL);
			return (-1);
		}
		if (new_pid == 0)
		{
			run_child_process_and_exit(envp, data, i);
		}
		data->commands[i]->pid = new_pid;
		i++;
	}
	return (0);
}
