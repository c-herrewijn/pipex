/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 15:07:12 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/03/24 14:10:35 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	validate_nr_argvars(int argc)
{
	// todo: remove always true!
	return (1); // alswys true!

	// if (argc != 5)
	if (argc < 5)
		return (0);
	else
		return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data		data;

	if (!validate_nr_argvars(argc))
		return (1);
	if (parsing(argc, argv, envp, &data) == -1)
		return (1);
	execute_commands_in_child_processes(envp, &data);

	// at very end, close outfile fildescriptor!
	return (0);
}
