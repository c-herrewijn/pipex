/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_argv.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 12:24:59 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/04/10 20:46:57 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
length of word up to next separator
ignores trailing spaces at end of word
*/
static size_t	word_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_separator_space(str, i) || is_trail_space(str, i))
			return (i);
		i++;
	}
	return (i);
}

/*
returns the nth word from a string
word_nr is 0-based
*/
static char	*create_word(char *str, size_t word_nr)
{
	size_t	w_count;
	size_t	i;
	char	*word_start;
	char	*word;

	w_count = 0;
	i = 0;
	while (w_count < word_nr)
	{
		if (is_separator_space(str, i))
			w_count++;
		i++;
	}
	word_start = str + i;
	while (*word_start != '\0' && ft_isspace(*word_start))
	{
		i++;
		word_start++;
	}
	word = ft_substr(str, i, word_len(word_start));
	return (trim_quotes(word));
}

/*
creates argument vector from a string
*/
static char	**split_argv(char *str, size_t *argc)
{
	char	**argv;
	size_t	nr_words;
	size_t	i_word;

	nr_words = count_words(str);
	argv = malloc((nr_words + 1) * sizeof(char *));
	if (argv == NULL)
		return (NULL);
	i_word = 0;
	while (i_word < nr_words)
	{
		argv[i_word] = create_word(str, i_word);
		if (argv[i_word] == NULL)
		{
			free_arr(argv);
			return (NULL);
		}
		i_word++;
	}
	argv[i_word] = NULL;
	*argc = nr_words;
	return (argv);
}

static t_command	*create_command(char *str)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->argv = split_argv(str, &(command->argc));
	if (command->argv == NULL)
		return (NULL);
	command->executable_location = NULL;
	return (command);
}

// assumes argc >= 5
void	parse_argv(char *argv[], t_data *data)
{
	size_t		i;
	t_command	**commands;
	t_command	*command;

	data->commands = NULL;
	commands = malloc((data->nr_commands + 1) * sizeof(t_command *));
	if (commands == NULL)
		return ;
	i = 0;
	while (i < data->nr_commands)
	{
		command = create_command(argv[i + 2]);
		if (command == NULL)
		{
			free_commands(commands);
			return ;
		}
		commands[i] = command;
		i++;
	}
	commands[i] = NULL;
	data->commands = commands;
}
