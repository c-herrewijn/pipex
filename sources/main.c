/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 15:07:12 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/03/22 13:28:21 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	validate_nr_argvars(int argc)
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
	t_data		data;

	if (!validate_nr_argvars(argc))
		return (1);
	data.nr_commands = (size_t)argc - 3;
	parse_argv(argc, argv, &data);
	if (data.commands == NULL)
		return (1);

	// if (!create_pipes(&data));
	// {
	// 	free_data(&data);
	// 	return (1);
	// }
	
	// if (!execute_commands(argc, argv, envp, &data));
	// {
	// 	free_data(&data);
	// 	return (1);
	// }
	return (0);
}
