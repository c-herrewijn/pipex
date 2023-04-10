#include "../libft/libft.h"
#include "../sources/pipex.h"
#include "test.h"


void	test_trim_quotes(void)
{
	char *str;
	char *trim_str;
	
	str = ft_strdup("abcde");
	trim_str = trim_quotes(str);
	printf("string:\n%s\n", str);
	printf("trimmed string:\n%s\n", trim_str);
	free(trim_str);
	
	str = ft_strdup("\"abcde\"");
	trim_str = trim_quotes(str);
	printf("string:\n%s\n", str);
	printf("trimmed string:\n%s\n", trim_str);
	free(trim_str);
	
	str = ft_strdup("'abcde'");
	trim_str = trim_quotes(str);
	printf("string:\n%s\n", str);
	printf("trimmed string:\n%s\n", trim_str);
	free(trim_str);
	
	str = ft_strdup("abcde'");
	trim_str = trim_quotes(str);
	printf("string:\n%s\n", str);
	printf("trimmed string:\n%s\n", trim_str);
	free(trim_str);
}
