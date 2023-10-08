#include "minishell.h"

void	minishell_pwd(void)
{
	char	buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	printf("%s\n", buf);
}
