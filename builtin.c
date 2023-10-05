#include "minishell.h"

void	minishell_exit(int exit_status)
{
	printf("exit\n");
	exit(exit_status);
}

void	minishell_cd(char *dir)
{
	if (!dir)
		chdir("/");
	else
		chdir(dir);
}

void	minishell_export(char **argv)
{
	int		fd;
	char	*name;
	char	*value;

	fd = open(".minishell_rc", O_RDWR);
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

void	minishell_unset(char **argv)
{
	int		fd;
	char	*name;
	char	*value;

	fd = open(".minishell_rc", O_RDWR);
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
