/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 20:33:06 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/04/06 15:42:07 by cherrewi      ########   odam.nl         */
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
	data->argc = argc;
	data->argv = argv;
	data->nr_commands = (size_t)argc - 3;
	data->nr_pipes = data->nr_commands - 1;
	data->paths = get_path(envp);
	parse_argv(argv, data);
	if (data->commands == NULL)
	{
		perror(NULL);
		return (-1);
	}
	create_pipes(data);
	if (data->pipes == NULL)
	{
		perror(NULL);
		return (-1);
	}
	return (0);
}
