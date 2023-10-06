#include "minishell.h"

static char	*ft_getenv(char *name)
{
	int		fd;
	char	*rc_path;
	char	*line;
	char	*value;

	rc_path = (ft_strjoin(getenv("HOME"), "/.minishell_rc"));
	fd = open(rc_path, O_RDWR);
	if (fd < 0)
		exit(1);
	value = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strncmp(line, name, ft_strlen(name)) && line[ft_strlen(name)] == '=')
		{
			value = ft_strdup(&(line[ft_strlen(name) + 1]));
			value[ft_strlen(value) - 1] = '\0';
		}
		free(line);
	}
	close (fd);
	return value;
}

void	env_init(char **envp)
{
	int		fd;
	char	*rc_path;

	rc_path = (ft_strjoin(getenv("HOME"), "/.minishell_rc"));
	fd = open(rc_path, O_RDWR);
	if (fd < 0)
		exit(1);
	while (*envp)
	{
		if (!ft_strncmp(*envp, "SHLVL=", 6))
		{
			ft_putstr_fd("SHLVL=", fd);
			ft_putnbr_fd(ft_atoi(&((*envp)[6])) + 1, fd);
		}
		else
		{
			ft_putstr_fd(*envp, fd);
		}
		ft_putchar_fd('\n', fd);
		envp ++;
	}
	close(fd);
}

void	env_translate(char **argv)
{
	char	*var;

	while (*argv)
	{
		if ((*argv)[0] == '$')
		{
			var = ft_getenv(&((*argv)[1]));
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
