#include "minishell.h"

static void	f1(char **argv, char *line)
{
	int			i;
	char		*trc_path;
	static int	fd;
	static bool	env_f;
	static bool	*argv_f;

	if (!line)
	{
		if (fd > 0)
		{
			i = 0;
			while (argv[++i])
			{
				if (argv_f[i])
					continue ;
				else if (!env_f && !invalid_identifier(argv[i]))
					printf("minishell: unset: `%s': not a valid identifier\n", argv[i]);
				else if (env_f && (!ft_strchr(argv[i], '=') || *(argv[i]) == '='))
					break ;
				else if (ft_strchr(argv[i], '='))
				{
					ft_putstr_fd(argv[i], fd);
					ft_putchar_fd('\n', fd);
				}
			}
			close(fd);
		}
		fd = 0;
		if (argv_f)
			free(argv_f);
		return ;
	}
	if (!fd)
	{
		trc_path = ft_strjoin(getenv("HOME"), TRC_PATH);
		fd = open(trc_path, (O_RDWR | O_TRUNC | O_CREAT), 0666);
		if (fd < 0)
			exit(1);
		free(trc_path);
		env_f = (!ft_strncmp(*argv, "env", 4));
		i = 0;
		while (argv[i])
			i ++;
		argv_f = (bool *)malloc(sizeof(bool) * i);
		ft_memset(argv_f, 0, i);
	}
	i = 0;
	while (argv[++i])
	{
		if (argv_f[i])
			continue ;
		else if (env_f && (!ft_strchr(argv[i], '=') || *(argv[i]) == '='))
			break ;
		else if (env_f
			|| (!ft_strncmp(line, argv[i], ft_strlen(argv[i]))
				&& line[ft_strlen(argv[i])] == '='))
		{
			argv_f[i] = 1;
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

void	minishell_unset(char **argv)
{
	char	*trc_path;

	env_loop(RC_PATH, argv, f1);
	env_loop(TRC_PATH, argv, f2);
	trc_path = ft_strjoin(getenv("HOME"), TRC_PATH);
	unlink(trc_path);
	free(trc_path);
}
