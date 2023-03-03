#include "../libft/libft.h"
#include "../sources/pipex.h"
#include "test.h"

static void testing_sep_space(char *str)
{
    int i;
    int result;
    char print_char;

    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    write(1, "\n", 1);
    i = 0;
    while (str[i])
    {
        result = is_separator_space(str, i);
        if (result < 0)
            print_char = 'X';
        else if (result == 0)
            print_char = '0';
        else if (result == 1)
            print_char = '1';
        write(1, &print_char, 1);
        i++;
    }
    write(1, "\n\n", 2);
}

void test_is_separator_space(void)
{
    testing_sep_space("ab  fghil");
    testing_sep_space("   abcde fghil    ");
    testing_sep_space("./'script space.sh'");
    testing_sep_space("awk \"{count++} END {printf \\\"count: \%i\\\" , count}\"");
    testing_sep_space("wc -c");
    testing_sep_space("wc 		-c");
    testing_sep_space("wc 		");
	testing_sep_space("  ");
}
