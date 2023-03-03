/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 17:12:40 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/03/03 12:14:17 by cherrewi      ########   odam.nl         */
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

static int	is_trail_space(char *str, size_t index)
{
	size_t	i;

	if (str == NULL || index >= ft_strlen(str) || str[index] != ' ')
		return (-1);
	i = 0;
	while (str[index + i] != '\0')
	{
		if (str[index + i] != ' ')
			return (0);
		i++;
	}	
	return (1);
}

/* checks if a space in a string counts a separator
/ spaces are separating if they are not consecutive spaces 
/ or within pairs of single or double quotes
*/
int	is_separator_space(char *str, size_t index)
{
	size_t				i;
	t_separator_state	state;

	state.open_squote = false;
	state.open_dquote = false;
	state.prev_space = true;
	state.escape_dquote = false;
	if (str == NULL || index >= ft_strlen(str) || str[index] != ' ')
		return (-1);
	if (is_trail_space(str, index))
		return (0);
	i = 0;
	while (i + 1 < index)
	{
		if (str[i] == ' ')
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
ignores spaces within quotes
assumes there are no trailing or leading spaces, and string is not empty
*/
int	count_words(char *str)
{
	int		words;
	size_t	i;
	int		is_split;

	words = 1;
	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == ' ')
		{
			is_split = is_separator_space(str, i);
			if (is_split == -1)
				return (-1);
			else if (is_split == true)
				words += 1;
		}
		i++;
	}
	return (words);
}
