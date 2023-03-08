/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_command.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 20:23:47 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/03/08 12:47:41 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_command	*create_command(char *str)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->argv = split_argv(str, &(command->argc));
	return (command);
}
