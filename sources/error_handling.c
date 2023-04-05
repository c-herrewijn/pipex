/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 16:05:58 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/04/05 17:18:49 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
			perror(command->argv[0]);
		else
			ft_printf_fd(2, "%s: command not found\n", command->argv[0]);
		exit(127);
	}
	perror(NULL);
	exit(1);
}
