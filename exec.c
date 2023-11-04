/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 05:43:58 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/04 19:07:15 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 引数のコマンドが存在するか確かめる。存在して、実行可能ならそのパスを返す。else NULLを返す。
char	*search_path(const char *filename)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;

	value = getenv("PATH");
	while (*value)
	{
		ft_bzero(path, PATH_MAX);
		end = ft_strchr(value, ':');
		if (end && end - value < 1024)
			ft_strlcpy(path, value, end - value + 1);
		else
			ft_strlcpy(path, value, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, filename, PATH_MAX);
		if (access(path, X_OK) == 0)
			return (accessible_path(&path[0]));
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}

int	exec_nonbuiltin(t_node *node, t_map *env)
{
	char		**argv;
	const char	*path;

	do_redirect(node->command->redirects);
	argv = token_list_to_argv(node->command->args);
	path = argv[0];
	if (ft_strchr(path, '/') == NULL)
		path = search_path(path);
	validate_access(path, argv[0]);
	execve(path, argv, get_environ(env));
	free_argv(argv);
	reset_redirect(node->command->redirects);
	fatal_error("execve");
}

pid_t	exec_pipeline(t_node *node, t_es *es)
{
	extern char	**environ;
	pid_t		pid;

	if (node == NULL)
		return (-1);
	prepare_pipe(node);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		reset_signals();
		prepare_pipe_child(node);
		if (is_builtin(node))
			exit(exec_builtin(node, es));
		else
			exec_nonbuiltin(node, es->env);
	}
	prepare_pipe_parent(node);
	if (node->next)
		return (exec_pipeline(node->next, es));
	return (pid);
}

int	wait_pipeline(pid_t last_pid)
{
	pid_t	wait_result;
	int		status;
	int		wstatus;

	while (1)
	{
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
		{
			if (WIFSIGNALED(wstatus))
				status = 128 + WTERMSIG(wstatus);
			else
				status = WEXITSTATUS(wstatus);
		}
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
			else if (errno == EINTR)
				continue ;
			else
				fatal_error("wait");
		}
	}
	return (status);
}

int	exec(t_node *node, t_es *es)
{
	int		status;
	pid_t	last_pid;

	if (open_redirect_file(node) < 0)
		return (ERROR_OPEN_REDIR);
	if (node->next == NULL && is_builtin(node))
		status = exec_builtin(node, es);
	else
	{
		last_pid = exec_pipeline(node, es);
		status = wait_pipeline(last_pid);
	}
	return (status);
}
