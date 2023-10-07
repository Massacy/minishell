#include "minishell.h"

void	minishell_cd(char *dir)
{
	if (!dir)
	{
		chdir("/");
	}
	else
	{
		chdir(dir);
	}
}
