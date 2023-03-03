#include "../libft/libft.h"
#include "../sources/pipex.h"
#include "test.h"


static void print_array(char **arr)
{
    int i;

    i = 0;
    while (arr[i] != NULL)
    {
        printf("|%s|\n", arr[i]);
        i++;
    }
}

void	test_split_argv(void)
{
    size_t nr_words;
    
    print_array(split_argv("      hallo     hallo ", &nr_words));
    printf("nr of words: %lu\n", nr_words);
    print_array(split_argv("hallo     hallo ", &nr_words));
    printf("nr of words: %lu\n", nr_words);
    print_array(split_argv("hallo     hallo", &nr_words));
    printf("nr of words: %lu\n", nr_words);
    print_array(split_argv("hallo  hallo", &nr_words));
    printf("nr of words: %lu\n", nr_words);
    print_array(split_argv("hallo hallo", &nr_words));
    printf("nr of words: %lu\n", nr_words);
    print_array(split_argv("awk \"{count++} END {printf \\\"count: \%i\\\" , count}\"", &nr_words));
    printf("nr of words: %lu\n", nr_words);
}
