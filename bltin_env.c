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
	char **tmp;

	if (!argv[1])
		env_loop(RC_PATH, argv, f);
	else
	{
		printf("[test] env start\n");
		if (ft_strchr(argv[1], '=') && *(argv[1]) != '=')
		{
			minishell_export(argv);
			printf("[test] env export: OK\n");
			tmp = argv + 1;
			while (*tmp && ft_strchr(*tmp, '=') && **tmp != '=')
				tmp ++;
			if (*tmp)
				interpret(tmp);
			printf("[test] env interpret: OK\n");
			minishell_unset(argv);
			printf("[test] env unset: OK\n");
		}
		else
		{
			interpret(argv + 1);
		}
	}
}
