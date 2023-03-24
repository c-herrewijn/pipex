#include "../libft/libft.h"
#include "../sources/pipex.h"
#include "test.h"

void	test_ft_printf_fd(void)
{
    ft_printf_fd(1, "hello %s\n", "world");
    ft_printf_fd(1, "pointer: %p\n", "world");
    ft_printf_fd(1, "number: %d\n", 42);
}
