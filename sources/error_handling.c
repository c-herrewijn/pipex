/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 16:05:58 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/04/05 18:15:59 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_child_errors(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nr_commands)
	{
		if (data->commands[i]->exit_status == 126)
		{
			ft_printf_fd(2, "%s: Permission denied\n",
				data->commands[i]->argv[0]);
		}
		else if (data->commands[i]->exit_status == 127)
		{			
			if (data->paths != NULL)
				ft_printf_fd(2, "%s: command not found\n",
					data->commands[i]->argv[0]);
		}
		i++;
	}
}

// exits child process with error
void	exit_with_error(t_command *command, char **paths)
{
	extern int	errno;

	if (errno == 13)
		exit(126);
	if (errno == 2)
	{
		if (paths == NULL)
			perror(command->argv[0]);
		exit(127);
	}
	perror(command->argv[0]);
	exit(1);
}
