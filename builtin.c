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

void	minishell_export(char **argv)
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

void	minishell_env(char **argv)
{
	int		fd;
	char	*rc_path;
	char	*line;

	rc_path = (ft_strjoin(getenv("HOME"), "/.minishell_rc"));
	fd = open(rc_path, O_RDWR);
	if (fd < 0)
		exit(1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	close (fd);
	(void)argv;
}

void	minishell_exit(int exit_status)
{
	printf("exit\n");
	exit(exit_status);
}
