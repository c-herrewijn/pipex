#include "../libft/libft.h"
#include "../sources/pipex.h"
#include "test.h"

void    test_is_trail_space(void)
{
    printf("0 - %d\n", is_trail_space("  aa  bb  ", 0));
    printf("0 - %d\n", is_trail_space("  aa  bb  ", 1));
    printf("0 - %d\n", is_trail_space("  aa  bb  ", 2));
    printf("0 - %d\n", is_trail_space("  aa  bb  ", 3));
    printf("0 - %d\n", is_trail_space("  aa  bb  ", 4));
    printf("0 - %d\n", is_trail_space("  aa  bb  ", 5));
    printf("0 - %d\n", is_trail_space("  aa  bb  ", 6));
    printf("0 - %d\n", is_trail_space("  aa  bb  ", 7));
    printf("1 - %d\n", is_trail_space("  aa  bb  ", 8));
    printf("1 - %d\n", is_trail_space("  aa  bb  ", 9));
    printf("0 - %d\n", is_trail_space("  aa  bb  ", 10));
}
