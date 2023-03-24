#include "../libft/libft.h"
#include "../sources/pipex.h"
#include "test.h"

int main(void)
{
    test_is_trail_space();
    test_is_separator_space();
    test_count_words();
    test_split_argv();
    test_create_command();
    test_ft_printf_fd();
}
