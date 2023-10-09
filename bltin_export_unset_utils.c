#include "minishell.c"

int	check_invalid_identifier(char *s)
{
	if (!*s)
		return (0);
	if (!ft_isalpha(*s) && *s != '_')
		return (1);
	s ++;
	while (*s && *s != '=')
	{
		if (!ft_isalnum(*s) && *s != '_')
			return (1);
		s ++;
	}
	return (0);
}

void	check_overlap_env_in_argv(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = i + 1;
		while (argv[j])
		{
			if (ft_strncmp(argv[i], argv[j], ft_strchr(argv[i], '=') - argv[i]))
			{
				*(argv[i]) = '\0';
				break ;
			}
			j ++;
		}
		i ++;
	}
}
