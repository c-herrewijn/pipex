/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 17:12:40 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/04/10 15:16:36 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	update_open_quote_status(t_separator_state *state, char c)
{
	if (c == '\'' && state->open_dquote == false)
	{
		if (state->open_squote == true)
			state->open_squote = false;
		else
		{
			if (state->prev_space == true)
				state->open_squote = true;
		}
	}
	if (c == '"' && state->open_squote == false
		&& state->escape_dquote == false)
	{
		if (state->open_dquote == true)
			state->open_dquote = false;
		else
		{				
			if (state->prev_space == true)
				state->open_dquote = true;
		}
	}
	state->prev_space = false;
}

bool	is_trail_space(char *str, size_t index)
{
	size_t	i;

	if (str == NULL || index >= ft_strlen(str) || !ft_isspace(str[index]))
		return (false);
	i = 0;
	while (str[index + i] != '\0')
	{
		if (!ft_isspace(str[index + i]))
			return (false);
		i++;
	}	
	return (true);
}

/* checks if a space in a string is a separator
/ in case of consecutive spaces, only the first one counts as separating
/ spaces within pairs of single or double quotes are not separating
*/
bool	is_separator_space(char *str, size_t index)
{
	size_t				i;
	t_separator_state	state;

	state.open_squote = false;
	state.open_dquote = false;
	state.prev_space = true;
	state.escape_dquote = false;
	if (str == NULL || index >= ft_strlen(str))
		return (false);
	if (!ft_isspace(str[index]) || is_trail_space(str, index))
		return (false);
	i = 0;
	while (i < index)
	{
		if (ft_isspace(str[i]))
			state.prev_space = true;
		else
			update_open_quote_status(&state, str[i]);
		if (str[i] == '\\')
			state.escape_dquote = !state.escape_dquote;
		else
			state.escape_dquote = false;
		i++;
	}
	return (!(state.prev_space || state.open_squote || state.open_dquote));
}

/* 
separates words based on spaces
ignores spaces within single or double quotes
*/
size_t	count_words(char *str)
{
	size_t	word_count;
	size_t	i;

	if (*str == '\0' || is_trail_space(str, 0))
		return (0);
	word_count = 1;
	i = 0;
	while (str[i] != '\0')
	{
		if (is_separator_space(str, i))
			word_count += 1;
		i++;
	}
	return (word_count);
}

/*
Trims a pair of single or double quotes from a string.
NOTE: assumes the imput string is malloc-ed!
If quotes need to be trimmed, the original string is freed 
and the return string is newly malloced
*/
char	*trim_quotes(char *word)
{
	size_t	len;
	size_t	i_end;
	char	*trimmed_word;

	if (word == NULL)
		return (NULL);
	len = ft_strlen(word);
	if (len < 2)
		return (word);
	i_end = len - 1;
	if ((word[0] == '\'' && word[i_end] == '\'')
		|| (word[0] == '"' && word[i_end] == '"'))
	{
		trimmed_word = ft_substr(word, 1, len - 2);
		free(word);
		return (trimmed_word);
	}
	else
		return (word);
}
