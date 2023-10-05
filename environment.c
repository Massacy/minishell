#include "minishell.h"

void	env_translate(char **argv)
{
	char	*var;

	while (*argv)
	{
		if ((*argv)[0] == '$')
		{
			var = getenv(&((*argv)[1]));
			if (!var)
				(*argv)[0] = '\0';
			else
			{
				free(*argv);
				*argv = var;
			}
		}
		argv ++;
	}
}
