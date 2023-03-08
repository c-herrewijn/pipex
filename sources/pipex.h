/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/18 18:09:20 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/03/08 13:55:29 by cherrewi      ########   odam.nl         */
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

typedef struct s_com
{
	size_t	argc;
	char	**argv;
}	t_command;

typedef struct s_terminal_fd
{
	int	fd_in;
	int	fd_out;
}	t_terminal_fds;

typedef struct s_separator_state
{
	bool	open_squote;
	bool	open_dquote;
	bool	prev_space;
	bool	escape_dquote;
}	t_separator_state;

t_command	**parse_argv(int argc, char *argv[]);
t_command	*create_command(char *str);
void		free_commands(t_command **commands);
char		**split_argv(char *str, size_t *argc);
bool		is_trail_space(char *str, size_t index);
bool		is_separator_space(char *str, size_t index);
size_t		count_words(char *str);
void		free_arr(char **arr);

#endif
