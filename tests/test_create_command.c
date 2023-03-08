#include "../libft/libft.h"
#include "../sources/pipex.h"
#include "test.h"

static void print_array(char **arr)
{
    int i;

    i = 0;
    while (arr[i] != NULL)
    {
        printf("argv[%d]: %s\n", i, arr[i]);
        i++;
    }
}


void test_create_command(void)
{
	t_command 		*com;
	char 			*com_str = "wc -c";
	
	com = create_command(com_str);
	
	printf("argc: %zu\n", com->argc);
	print_array(com->argv);
}
