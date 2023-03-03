/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 15:07:12 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/03/03 10:01:19 by cherrewi      ########   odam.nl         */
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
	int			terminal_in_fd;
	int			terminal_out_fd;
	t_com		**commands;
	t_term_fds	term_fds;

	if (!validate_nr_argvars(argc))
		return (1);
	terminal_in_fd = dup(STDIN_FILENO);
	terminal_out_fd = dup(STDOUT_FILENO);
	if (terminal_out_fd < 0 || terminal_in_fd < 0)
		return (1);
	term_fds.fd_in = terminal_in_fd;
	term_fds.fd_out = terminal_out_fd;

	// todo
	//commands = parse_argv(argc, argv, envp, term_fds);
	//execute_commands(commands);

	return (0);
}
