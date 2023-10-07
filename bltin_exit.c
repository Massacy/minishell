#include "minishell.h"

void	minishell_exit(int exit_status)
{
	printf("exit\n");
	exit(exit_status);
}
