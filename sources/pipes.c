/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 13:50:19 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/03/24 13:55:27 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipes(t_data *data)
{
	size_t	i;
	int		result;

	data->pipes = malloc(data->nr_pipes * 2 * sizeof(int));
	if (data->pipes == NULL)
		return ;
	i = 0;
	while (i < data->nr_pipes)
	{
		result = pipe(data->pipes[i]);
		if (result < 0)
		{
			free(data->pipes);
			data->pipes = NULL;
			return ;
		}
		i++;
	}
}

int	close_pipes_before_running_command_i(t_data *data, size_t i_command)
{
	size_t	i_pipe;

	i_pipe = 0;
	while (i_pipe < data->nr_pipes)
	{
		if (!(i_command == i_pipe + 1))
		{
			if (close(data->pipes[i_pipe][0]) < 0)
				return (-1);
		}
		if (!(i_command == i_pipe))
		{
			if (close(data->pipes[i_pipe][1]) < 0)
				return (-1);
		}
		i_pipe++;
	}
	return (1);
}

int	close_all_pipes(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nr_pipes)
	{
		if (close(data->pipes[i][0]) < 0)
			return (-1);
		if (close(data->pipes[i][1]) < 0)
			return (-1);
		i++;
	}
	return (1);
}
