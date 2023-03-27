/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 20:33:06 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/03/27 15:49:44 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// stores path char ** in new memory
static char	**get_path(char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

int	parsing(int argc, char *argv[], char *envp[], t_data *data)
{
	data->nr_commands = (size_t)argc - 3;
	data->nr_pipes = data->nr_commands - 1;
	data->fd_infile = open(argv[1], O_RDONLY);
	if (data->fd_infile == -1)
		return (-1);
	data->fd_outfile = open(argv[argc - 1], O_CREAT | O_WRONLY, 0644);
	if (data->fd_outfile == -1)
		return (-1);
	data->paths = get_path(envp);
	parse_argv(argv, data);
	if (data->commands == NULL)
	{
		free(data->paths);
		return (-1);
	}
	create_pipes(data);
	if (data->pipes == NULL)
	{
		free(data->paths);
		free_commands(data->commands);
		return (-1);
	}
	return (0);
}
