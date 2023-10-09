#include "minishell.h"

void	minishell_echo(char **argv)
{
	bool	f;

	f = ft_strncmp(argv[1], "-n", 3);
	if (!f)
		argv ++;
	while (*(++argv))
	{
		printf("%s", *argv);
		printf("%c", !(!argv[1]) * ' ');
	}
	if (f)
		printf("\n");
}
