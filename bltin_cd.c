#include "minishell.h"

void	minishell_cd(char *dir)
{
	int		r;
	char	*tmp;
	char	**argv;
	char	buf[PATH_MAX];

	if (!dir)
		r = chdir(getenv("HOME"));
	else
	{
		tmp = dir;
		if (*dir == '~')
			dir = ft_strjoin(getenv("HOME"), dir + 1);
		r = chdir(dir);
		if (tmp != dir)
			free(dir);
		dir = tmp;
	}
	if (r < 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", dir);
		return ;
	}
	getcwd(buf, PATH_MAX);
	argv = (char **)malloc(sizeof(char *) * 4);
	argv[0] = ft_strdup("export");
	argv[1] = ft_strjoin("PWD=", buf);
	argv[2] = ft_strjoin("OLDPWD=", ft_getenv("PWD"));
	argv[3] = NULL;
	minishell_export(argv);
	free(argv[0]);
	free(argv[1]);
	free(argv);
}
