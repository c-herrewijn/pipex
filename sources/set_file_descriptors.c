/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_file_descriptors.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 16:14:14 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/04/04 16:16:44 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	set_filedescriptors(t_data *data, size_t i_command)
{
	int	fd_infile;
	int	fd_outfile;

	if (i_command == 0)
	{
		fd_infile = open(data->argv[1], O_RDONLY);
		if (fd_infile == -1)
		{
			print_file_error(data->argv[1]);
			return (-1);
		}
		if (dup2(fd_infile, STDIN_FILENO) == -1)
		{
			print_gereral_error();
			return (-1);
		}
	}
	else
	{
		if (dup2(data->pipes[i_command - 1][0], STDIN_FILENO) == -1)
		{
			print_gereral_error();
			return (-1);
		}
	}
	if (i_command + 1 == data->nr_commands)
	{
		fd_outfile = open(data->argv[data->argc - 1], O_CREAT | O_WRONLY, 0644);
		if (fd_outfile == -1)
		{
			print_file_error(data->argv[data->argc - 1]);
			return (-1);
		}
		if (dup2(fd_outfile, STDOUT_FILENO) == -1)
		{
			print_gereral_error();
			return (-1);
		}
	}
	else
	{
		if (dup2(data->pipes[i_command][1], STDOUT_FILENO) == -1)
		{
			print_gereral_error();
			return (-1);
		}
	}
	return (1);
}
