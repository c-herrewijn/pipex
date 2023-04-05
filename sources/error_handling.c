/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 16:05:58 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/04/05 13:31:27 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// print errno file error
void	print_file_error(char *file)
{
	ft_printf_fd(2, "%s: ", file);
	perror(NULL);
}

// print errno general error
void	print_gereral_error(void)
{
	perror(NULL);
}

// exits child process with error
void	exit_with_error(t_command *command, char **paths)
{
	extern int	errno;

	if (errno == 13)
	{
		ft_printf_fd(2, "%s: Permission denied\n", command->argv[0]);
		exit(126);
	}
	if (errno == 2)
	{
		if (paths == NULL)
			print_file_error(command->argv[0]);
		else
			ft_printf_fd(2, "%s: command not found\n", command->argv[0]);
		exit(127);
	}
	print_gereral_error();
	exit(1);
}
