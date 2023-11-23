/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 05:49:04 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/23 19:12:31 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*accessible_path(char *path)
{
	char	*dup;

	dup = ft_strdup(path);
	if (dup == NULL)
		fatal_error("strdup");
	return (dup);
}

static int	count_argv(char **argv)
{
	int	cnt;

	cnt = 0;
	while (argv[cnt] != NULL)
		cnt++;
	return (cnt);
}

void	validate_access(char *path, char **argv)
{
	struct stat	st;
	char		*filename;
	int			argc;

	filename = argv[0];
	argc = count_argv(argv);
	if (path == NULL || ft_strcmp(filename, "") == 0 || ft_strcmp(filename,
			"..") == 0)
		err_exit(filename, "command not found", 127);
	if (ft_strcmp(filename, ".") == 0 && argc == 1)
		err_exit(filename, "filename argument required", 2);
	if (access(path, F_OK) < 0)
		err_exit(filename, "No such file or directory", 127);
	if (stat(path, &st) < 0)
		fatal_error("fstat");
	if (ft_strcmp(filename, ".") != 0 && S_ISDIR(st.st_mode))
		err_exit(filename, "is a directory", 126);
	if (access(path, X_OK) < 0)
		err_exit(filename, "Permission denied", 126);
}

/*
	t_tokenの線形リストをchar**に変換する。
	・線形リストの要素数を数える。
	・char**をcallocで確保する。
	・線形リストを順番に回して、char**にwordをコピーしていく。
	・char**の最後にNULLを入れる。
	※ wordは線形リスト内のポインタを指しているので、このargv使用中はtokをfreeしてはいけない。
*/
char	**token_list_to_argv(t_token *tok)
{
	char	**argv;
	int		cnt;
	int		i;
	t_token	*cur;

	cnt = 0;
	cur = tok;
	while (cur != NULL)
	{
		cnt++;
		cur = cur->next;
	}
	argv = ft_calloc(cnt + 1, sizeof(char *));
	if (argv == NULL)
		fatal_error("calloc");
	cur = tok;
	i = -1;
	while (++i < cnt)
	{
		argv[i] = ft_strdup(cur->word);
		cur = cur->next;
	}
	argv[i] = NULL;
	return (argv);
}
