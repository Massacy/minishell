#include "minishell.h"

char	*ft_getenv(char *name)
{
	int		i;
	int		fd;
	char	*rc_path;
	char	*line;
	char	*value;

	rc_path = (ft_strjoin(getenv("HOME"), RC_PATH));
	fd = open(rc_path, O_RDWR);
	if (fd < 0)
		exit(1);
	i = 0;
	while (ft_isalnum(name[i]) || name[i] == '_')
		i ++;
	value = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strncmp(line, name, i) && line[i] == '=')
		{
			value = ft_strdup(&(line[i + 1]));
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

	rc_path = (ft_strjoin(getenv("HOME"), RC_PATH));
	fd = open(rc_path, (O_RDWR | O_TRUNC | O_CREAT), 0666);
	if (fd < 0)
		exit(1);
	while (*envp)
	{
		if (!ft_strncmp(*envp, "SHLVL=", 6))
		{
			ft_putstr_fd("SHLVL=", fd);
			ft_putnbr_fd(ft_atoi(&((*envp)[6])) + 1, fd);
			ft_putchar_fd('\n', fd);
		}
		else if (ft_strncmp(*envp, "OLDPWD=", 7))
		{
			ft_putstr_fd(*envp, fd);
			ft_putchar_fd('\n', fd);
		}
		envp ++;
	}
	close(fd);
}

void	env_translate(char **argv)
{
	int		i;
	int		s_i;
	char	*tmp1;
	char	*tmp2;
	char	*var;

	while (*argv)
	{
		s_i = 0;
		while ((*argv)[s_i])
		{
			if ((*argv)[s_i] == '$'
				&& (ft_isalpha((*argv)[s_i + 1]) || (*argv)[s_i + 1] == '_'))
			{
				i = 1;
				while (ft_isalnum((*argv)[s_i + i])
					|| (*argv)[s_i + i] == '_')
					i ++;
				(*argv)[s_i] = '\0';
				tmp1 = *argv;
				var = ft_getenv(&((*argv)[s_i + 1]));
				if (!var)
					*argv = ft_strjoin(*argv, &((*argv)[s_i + i]));
				else
				{
					tmp2 = ft_strjoin(*argv, var);
					free(var);
					*argv = ft_strjoin(tmp2, &((*argv)[s_i + i]));
					free(tmp2);
				}
				free(tmp1);
			}
			else
				s_i ++;
		}
		argv ++;
	}
}

void	env_loop(char *rc_file, char **argv, void f(char **, char *))
{
	int		fd;
	char	*line;
	char	*rc_path;

	rc_path = ft_strjoin(getenv("HOME"), rc_file);
	fd = open(rc_path, O_RDWR);
	if (fd < 0)
		exit(1);
	free(rc_path);
	while (1)
	{
		line = get_next_line(fd);
		f(argv, line);
		if (!line)
			break ;
		free(line);
	}
	close (fd);
}
