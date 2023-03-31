/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 15:07:12 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/03/31 18:07:29 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	validate_nr_argvars(int argc)
{
	if (argc != 5)
		return (0);
	else
		return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data		data;
	int			final_command_index;
	int			exit_status;

	if (!validate_nr_argvars(argc))
		return (1);
	if (parsing(argc, argv, envp, &data) == -1)
		return (1);
	if (execute_commands_in_child_processes(envp, &data) == -1)
		return (1);

	// at very end, close outfile fildescriptor and free data struct!
	final_command_index = data.nr_commands - 1;
	exit_status = data.commands[final_command_index]->exit_status;
	return (exit_status);
}
