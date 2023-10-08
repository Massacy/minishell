#include "minishell.h"

static void	f1(char **argv, char *line)
{
	char		*trc_path;
	static int	fd;

	if (!line)
	{
		if (fd > 0)
		{
			while (*(++argv))
			{
				if (!invalid_identifier(*argv))
					printf("minishell: export: `%s': not a valid identifier\n", *argv);
				else if (**argv && ft_strchr(*argv, '='))
				{
					ft_putstr_fd(*argv, fd);
					ft_putchar_fd('\n', fd);
				}
			}
			close(fd);
		}
		fd = 0;
		return ;
	}
	if (!fd)
	{
		trc_path = ft_strjoin(getenv("HOME"), TRC_PATH);
		fd = open(trc_path, (O_RDWR | O_TRUNC | O_CREAT), 0666);
		if (fd < 0)
			exit(1);
		free(trc_path);
	}
	while (*(++argv))
	{
		if (ft_strchr(*argv, '=') && (*argv)[0] != '='
			&& !ft_strncmp(line, *argv, ft_strchr(*argv, '=') - *argv))
		{
			ft_putstr_fd(*argv, fd);
			ft_putchar_fd('\n', fd);
			**argv = '\0';
			return ;
		}
	}
	ft_putstr_fd(line, fd);
}

static void	f2(char **argv, char *line)
{
	char		*rc_path;
	static int	fd;

	if (!line)
	{
		if (fd > 0)
			close(fd);
		fd = 0;
		return ;
	}
	if (!fd)
	{
		rc_path = ft_strjoin(getenv("HOME"), RC_PATH);
		fd = open(rc_path, (O_RDWR | O_TRUNC | O_CREAT), 0666);
		if (fd < 0)
			exit(1);
		free(rc_path);
	}
	ft_putstr_fd(line, fd);
	(void)argv;
}

static void	f3(char **argv, char *line)
{
	char	*p;

	if (!line)
		return ;
	p = ft_strchr(line, '=');
	ft_putstr_fd("declare -x ", 1);
	write(1, line, (p - line) + 1);
	ft_putchar_fd('\"', 1);
	if (ft_strlen(p + 1))
		write(1, p + 1, ft_strlen(p + 1) - 1);
	ft_putstr_fd("\"\n", 1);
	(void)argv;
}

void	minishell_export(char **argv)
{
	char	*trc_path;

	if (argv[1])
	{
		env_loop(RC_PATH, argv, f1);
		env_loop(TRC_PATH, argv, f2);
		trc_path = ft_strjoin(getenv("HOME"), TRC_PATH);
		unlink(trc_path);
		free(trc_path);
	}
	else
	{
		env_loop(RC_PATH, argv, f3);
	}
}
