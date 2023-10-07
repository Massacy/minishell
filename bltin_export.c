#include "minishell.h"

static void	f(char **argv, char *line)
{
	// char		*rc_path;
	// char		*name;
	// static int	fd;

	// if (!line)
	// {
	// 	close(fd);
	// 	fd = 0;
	// 	return ;
	// }
	// if (!fd)
	// {
	// 	rc_path = ft_strjoin(getenv("HOME"), "/.minishell_rc");
	// 	fd = open(rc_path, O_RDWR);
	// 	if (fd < 0)
	// 		exit(1);
	// 	free(rc_path);
	// }
	// while (*argv)
	// {
	// 	name = ft_strdup(*argv);
	// 	if (ft_strchr(*argv, '='))
	// 	if (ft_strchr(*argv, '=')
	// 		&& !ft_strncmp(line, *argv, ft_strchr(*argv, '=') - *argv + 1))
	// 		ft_putstr_fd(*argv, fd);
	// 	else
	// 		ft_putstr_fd(line, fd);
	// 	argv ++;
	// }
	(void)argv;
	(void)line;
}

void	minishell_export(char **argv)
{
	env_loop(argv, f);
}
