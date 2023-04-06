/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 16:05:58 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/04/06 17:42:07 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
frees the string array
*/
void	free_arr(char **arr)
{
	int	i;

	if (arr != NULL)
	{
		i = 0;
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

/*
frees the commands array 
*/
void	free_commands(t_command **commands)
{
	int	i;

	if (commands != NULL)
	{
		i = 0;
		while (commands[i])
		{
			free_arr(commands[i]->argv);
			if (commands[i]->executable_location != NULL)
				free(commands[i]->executable_location);
			free(commands[i]);
			i++;
		}
		free(commands);
	}
}

void	print_child_errors(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nr_commands)
	{
		if (data->commands[i]->exit_status == 127)
		{			
			if (data->paths != NULL)
				ft_printf_fd(STDERR_FILENO, "%s: command not found\n",
					data->commands[i]->argv[0]);
		}
		i++;
	}
}

// exits child process with error
void	exit_with_error(t_command *command, char **paths)
{
	extern int	errno;

	if (errno == EACCES)
	{
		perror(command->executable_location);
		exit(126);
	}
	if (errno == ENOENT)
	{
		if (paths == NULL)
			perror(command->argv[0]);
		exit(127);
	}
	perror(command->argv[0]);
	exit(1);
}
