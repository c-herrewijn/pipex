/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/18 18:09:20 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/03/03 17:29:41 by cherrewi      ########   odam.nl         */
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
	int		argc;
	char	**argv;
	char	**environ;
	char	*command;  // todo: redundant, because equals argv[0]
	int		pipe_in[2];
	int		pipe_out[2];
	int		exit_code;
}	t_com;

typedef struct s_terminal_fd
{
	int	fd_in;
	int	fd_out;
}	t_term_fds;

typedef struct s_separator_state
{
	bool	open_squote;
	bool	open_dquote;
	bool	prev_space;
	bool	escape_dquote;
}	t_separator_state;

t_com	**parse_argv(int argc, char *argv[], char *envp[], t_term_fds term_fds);
char    **split_argv(char *str, size_t *argc);
bool	is_trail_space(char *str, size_t index);
bool	is_separator_space(char *str, size_t index);
size_t	count_words(char *str);

#endif
