/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 15:07:12 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/03/08 14:01:13 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	validate_nr_argvars(int argc)
{
	// todo: remove always true!
	return (1); // alswys true!

	if (argc != 5)
		return (0);
	else
		return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_command		**commands;

	if (!validate_nr_argvars(argc))
		return (1);

	commands = parse_argv(argc, argv);

	//execute_commands(commands);
	return (0);
}
