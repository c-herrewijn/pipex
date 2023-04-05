/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_commands.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 15:33:53 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/04/05 18:02:00 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute_command(char **envp, char **paths, t_command *command)
{
	int			i;
	extern int	errno;

	i = 0;
	command->executable_location = NULL;
	if (paths == NULL)
	{
		if (command->executable_location != NULL)
			free(command->executable_location);
		command->executable_location = command->argv[0];
		execve(command->executable_location, command->argv, envp);
	}
	else
	{
		while (paths[i] != NULL)
		{
			if (command->executable_location != NULL)
				free(command->executable_location);
			command->executable_location
				= combine_command_path(paths[i], command->argv[0]);
			execve(command->executable_location, command->argv, envp);
			i++;
		}
	}
	exit_with_error(command, paths);
}

static int	wait_for_child_processes(t_data *data)
{
	size_t	i;
	pid_t	return_pid;
	int		stat_loc;

	i = 0;
	while (i < data->nr_commands)
	{
		return_pid = waitpid(data->commands[i]->pid, &stat_loc, 0);
		if (return_pid == -1)
			return (-1);
		data->commands[i]->exit_status = WEXITSTATUS(stat_loc);
		i++;
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
		data->commands[i]->pid = new_pid;
		i++;
	}
	if (close_all_pipes(data) < 0 || wait_for_child_processes(data) < 0)
		return (-1);
	print_child_errors(data);
	return (1);
}
