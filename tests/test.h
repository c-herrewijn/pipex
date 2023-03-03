# include "../sources/pipex.h"

int			is_trail_space(char *str, size_t index);
int			is_separator_space(char *str, size_t index);
int			count_words(char *str);
static void	update_open_quote_status(t_separator_state *state, char c);

void		test_is_trail_space(void);
