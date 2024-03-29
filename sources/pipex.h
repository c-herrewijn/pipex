/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/18 18:09:20 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/04/10 14:52:19 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct s_command
{
	size_t	argc;
	char	**argv;
	char	*executable_location;
	pid_t	pid;
	int		exit_status;
}	t_command;

typedef struct s_data
{
	size_t		argc;
	char		**argv;
	size_t		nr_commands;
	size_t		nr_pipes;
	char		**paths;
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

int			parsing(int argc, char *argv[], char *envp[], t_data *data);
void		parse_argv(char *argv[], t_data *data);
void		free_arr(char **arr);
void		free_commands(t_command **commands);
bool		is_trail_space(char *str, size_t index);
bool		is_separator_space(char *str, size_t index);
size_t		count_words(char *str);
int			execute_commands_in_child_processes(char **envp, t_data *data);
int			wait_for_child_processes(t_data *data);
void		create_pipes(t_data *data);
int			close_all_pipes(t_data *data);
int			close_pipes_before_running_command_i(t_data *data,
				size_t i_command);
char		*combine_command_path(char *path, char *cmd);
void		exit_with_error(t_command *command, char **paths);
int			set_filedescriptors(t_data *data, size_t i_command);
void		print_child_errors(t_data *data);
char		*trim_quotes(char *word);

#endif
