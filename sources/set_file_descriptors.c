/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_file_descriptors.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 16:14:14 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/04/07 17:06:33 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	set_fd_infile(t_data *data)
{
	int	fd_infile;

	fd_infile = open(data->argv[1], O_RDONLY);
	if (fd_infile == -1)
	{
		perror(data->argv[1]);
		return (-1);
	}
	if (dup2(fd_infile, STDIN_FILENO) == -1)
	{
		perror(NULL);
		return (-1);
	}
	return (0);
}

static int	set_fd_outfile(t_data *data)
{
	int	fd_outfile;

	fd_outfile = open(data->argv[data->argc - 1], O_CREAT | O_WRONLY, 0644);
	if (fd_outfile == -1)
	{
		perror(data->argv[data->argc - 1]);
		return (-1);
	}
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
	{
		perror(NULL);
		return (-1);
	}
	return (0);
}

static int	set_fd_pipe_in(t_data *data, size_t i_command)
{
	if (dup2(data->pipes[i_command - 1][0], STDIN_FILENO) == -1)
	{
		perror(NULL);
		return (-1);
	}
	return (0);
}

static int	set_fd_pipe_out(t_data *data, size_t i_command)
{
	if (dup2(data->pipes[i_command][1], STDOUT_FILENO) == -1)
	{
		perror(NULL);
		return (-1);
	}
	return (0);
}

int	set_filedescriptors(t_data *data, size_t i_command)
{
	if (i_command == 0)
	{
		if (set_fd_infile(data) < 0)
			return (-1);
	}
	else
	{
		if (set_fd_pipe_in(data, i_command) < 0)
			return (-1);
	}
	if (i_command + 1 == data->nr_commands)
	{
		if (set_fd_outfile(data) < 0)
			return (-1);
	}
	else
	{
		if (set_fd_pipe_out(data, i_command) < 0)
			return (-1);
	}
	return (0);
}
