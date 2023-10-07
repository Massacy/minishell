#include "minishell.h"

static void	f(char **argv, char *line)
{
	if (!line)
		return ;
	printf("%s", line);
	(void)argv;
}

void	minishell_env(char **argv)
{
	env_loop(RC_PATH, argv, f);
}
