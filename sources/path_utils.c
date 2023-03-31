/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 18:11:39 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/03/31 18:13:51 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*combine_command_path(char *path, char *cmd)
{
	char	*command_path;
	size_t	malloc_len;

	malloc_len = ft_strlen(path) + ft_strlen("/") + ft_strlen(cmd) + 1;
	command_path = malloc(malloc_len * sizeof(char));
	if (command_path == NULL)
		return (NULL);
	ft_strlcpy(command_path, path, malloc_len);
	ft_strlcat(command_path, "/", malloc_len);
	ft_strlcat(command_path, cmd, malloc_len);
	return (command_path);
}
