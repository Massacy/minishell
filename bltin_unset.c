#include "minishell.h"

void	minishell_unset(char **argv)
{
	int		fd;
	char	*rc_path;
	char	*name;
	char	*value;

	rc_path = (ft_strjoin(getenv("HOME"), "/.minishell_rc"));
	fd = open(rc_path, O_RDWR);
	if (fd < 0)
		exit(1);
	argv ++;
	while (*argv)
	{
		argv ++;
	}
	close(fd);
	(void)name;
	(void)value;
}
