/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 15:07:12 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/04/06 16:22:02 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	is_valid_argc(int argc)
{
	if (argc == 5)
		return (true);
	else
		return (false);
}

static void	free_data_struct(t_data *data)
{
	free_arr(data->paths);
	free_commands(data->commands);
	free(data->pipes);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data		data;
	int			final_command_index;
	int			exit_status;

	if (!is_valid_argc(argc))
		return (1);
	if (parsing(argc, argv, envp, &data) < 0
		|| execute_commands_in_child_processes(envp, &data) < 0
		|| close_all_pipes(&data) < 0
		|| wait_for_child_processes(&data) < 0)
	{
		free_data_struct(&data);
		return (1);
	}
	print_child_errors(&data);
	final_command_index = data.nr_commands - 1;
	exit_status = data.commands[final_command_index]->exit_status;
	free_data_struct(&data);
	return (exit_status);
}
