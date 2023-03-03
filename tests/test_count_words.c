#include "../libft/libft.h"
#include "../sources/pipex.h"
#include "test.h"

void test_count_words(void)
{
	printf("2 - %zu\n", count_words("awk '{count++} END {print count}'"));
	printf("2 - %zu\n", count_words("awk \"{count++} END {print count}\""));
	printf("2 - %zu\n", count_words("awk \"{count++} END {printf \\\"count: \%i\\\" , count}\""));
	printf("2 - %zu\n", count_words("awk '{count++} END {printf \"count: %i\" count}'"));
	printf("2 - %zu\n", count_words("awk \"{count++} END {printf \\\"c\\o\\ unt: \%i\\\", count}\""));
	printf("1 - %zu\n", count_words("\"end of line\""));
	printf("1 - %zu\n", count_words("'\"\"'"));
	printf("1 - %zu\n", count_words("\"./script space.sh\""));
	printf("1 - %zu\n", count_words("./\"script\\\"quote.sh\""));
	printf("1 - %zu\n", count_words("./middle_fail.sh"));
	printf("1 - %zu\n", count_words("./no_x_script.sh"));
	printf("1 - %zu\n", count_words("./script.sh"));
	printf("1 - %zu\n", count_words("\"EOF\""));
	printf("1 - %zu\n", count_words("subdir/script.sh"));
	printf("1 - %zu\n", count_words("uname"));
	printf("1 - %zu\n", count_words("wc"));
	printf("1 - %zu\n", count_words("  aa'bb"));
	printf("1 - %zu\n", count_words("aa'bb"));
	printf("1 - %zu\n", count_words("aabb"));
	printf("2 - %zu\n", count_words("aa' bb"));
	printf("2 - %zu\n", count_words("cat -e"));
	printf("2 - %zu\n", count_words("grep And"));
	printf("2 - %zu\n", count_words("grep But"));
	printf("2 - %zu\n", count_words("sed    \"s/And/But/\""));
	printf("2 - %zu\n", count_words("sed \"s/And/But/\""));
	printf("2 - %zu\n", count_words("sed \"s/And/But/\""));
	printf("2 - %zu\n", count_words("-la -d"));
	printf("2 - %zu\n", count_words("-la '-d'"));
	printf("2 - %zu\n", count_words("\"-'l\" -d"));
	printf("2 - %zu\n", count_words("aa  bb"));
	printf("2 - %zu\n", count_words("aa bb"));
	printf("2 - %zu\n", count_words("cat -e"));
	printf("2 - %zu\n", count_words("hallo  hallo"));
}
