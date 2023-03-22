/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/18 18:09:20 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/03/22 16:21:26 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../libft/libft.h"

// todo: add command_path to struct: this is the string with the actual command path, and needs to be freed.
typedef struct s_command
{
	size_t	argc;
	char	**argv;
}	t_command;

typedef struct s_data
{
	size_t		nr_commands;
	size_t		nr_pipes;
	t_command	**commands;
	int			(*pipes)[2];
}	t_data;

typedef struct s_separator_state
{
	bool	open_squote;
	bool	open_dquote;
	bool	prev_space;
	bool	escape_dquote;
}	t_separator_state;

void		parse_argv(int argc, char *argv[], t_data *data);
t_command	*create_command(char *str);
void		free_commands(t_command **commands);
char		**split_argv(char *str, size_t *argc);
bool		is_trail_space(char *str, size_t index);
bool		is_separator_space(char *str, size_t index);
size_t		count_words(char *str);
void		free_arr(char **arr);
int			execute_commands(int argc, char **argv, char **envp,
				t_command **commands);
void		create_pipes(t_data *data);

#endif
