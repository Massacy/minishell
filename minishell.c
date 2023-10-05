/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 06:01:01 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/06 06:29:41 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}

// void	fatal_error(const char *msg) __attribute__((noreturn));

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
		argv[i] = cur->word;
		cur = cur->next;
	}
	argv[i] = NULL;
	return (argv);
}

// TODO あとで、↑と↓の違いをみておく。

// char	**tail_recursive(t_token *tok, char **argv)
// {
// 	int nargs;

// 	nargs = 0;
// 	while (1)
// 	{
// 		// char **argv_cpy;
// 		if (tok == NULL || tok->kind == TK_EOF)
// 			return (argv);
// 		// argv_cpy = malloc((nargs + 2) * sizeof(char *));
// 		// memcpy(argv_cpy, argv, nargs);
// 		// free(argv);
// 		// nargs     = 0 -> 1
// 		//               ↓+2
// 		// argv.size = 2 -> 3
// 		argv = realloc(argv, (nargs + 2) * sizeof(char *));
// 		if (argv == NULL)
// 			fatal_error("reallocf");
// 		argv[nargs] = ft_strdup(tok->word);
// 		if (argv[nargs] == NULL)
// 			fatal_error("strdup");
// 		argv[nargs + 1] = NULL;
// 		tok = tok->next;
// 		nargs = nargs + 1;
// 	}
// }

// char	**token_list_to_argv(t_token *tok)
// {
// 	char	**argv;

// 	argv = ft_calloc(1, sizeof(char *));
// 	if (argv == NULL)
// 		fatal_error("calloc");

// 	return (tail_recursive(tok, argv));
// }

void	echo_args(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		printf("%s", split[i]);
		if (split[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

void	exec_built_in(char **split)
{
	if (split[0] != NULL)
	{
		if (ft_strlen(split[0]) == 4 && ft_strncmp(split[0], "echo", 4) == 0)
		{
			if (split[1] == NULL)
				printf("\n");
			else if (ft_strlen(split[1]) == 2 && ft_strncmp(split[1], "-n",
						2) == 0)
				echo_args(&split[2]);
			else
			{
				echo_args(&split[1]);
				printf("\n");
			}
		}
		else
			printf("this is not echo comamnd\n");
	}
}

void	validate_access(const char *path, const char *filename)
{
	if (path == NULL)
		err_exit(filename, "command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
}

int	exec_pipeline(t_node *node)
{
	extern char	**environ;
	const char	*path;
	pid_t		pid;
	char		**argv;

	if (node == NULL)
		return (-1);
	prepare_pipe(node);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		// child process
		prepare_pipe_child(node);
		do_redirect(node->command->redirects);
		argv = token_list_to_argv(node->command->args);
		path = argv[0];
		if (ft_strchr(path, '/') == NULL)
			path = search_path(path);
		validate_access(path, argv[0]);
		execve(path, argv, environ);
		reset_redirect(node->command->redirects);
		fatal_error("execve");
	}
	prepare_pipe_parent(node);
	if (node->next)
		return (exec_pipeline(node->next));
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
			status = WEXITSTATUS(wstatus); // TODO 使っていいか確認
			// status = wstatus & 255; // 動かない
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
		}
	}
	waitpid(last_pid, &wstatus, 0);
	return (status);
}

int	exec(t_node *node)
{
	int		status;
	pid_t	last_pid;

	if (open_redirect_file(node) < 0)
		return (ERROR_OPEN_REDIR);
	last_pid = exec_pipeline(node);
	status = wait_pipeline(last_pid);
	return (status);
}

// 子プロセスで*lineに入っているコマンドを実行する。
void	interpret(char *line, int *stat_loc)
{
	t_token	*tok;
	t_node	*node;
	bool	syntax_error;

	syntax_error = false;
	tok = tokenize(line, &syntax_error);
	if (at_eof(tok))
		;
	else if (syntax_error)
		*stat_loc = ERROR_TOKENIZE;
	else
	{
		node = parse(tok, &syntax_error);
		if (syntax_error)
			*stat_loc = ERROR_PARSE;
		else
		{
			expand(node);
			*stat_loc = exec(node);
		}
		free_node(node);
	}
	free_tok(tok);
}

char *accessible_pass(char *path)
{
	char	*dup;
	
	dup = ft_strdup(path);
	if (dup == NULL)
		fatal_error("strdup");
	return (dup);
}

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
			return (accessible_pass(&path[0]));
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}

// __attribute__((destructor))
// static void destructor() {
//     // system("leaks -q a.out");
//     system("leaks -q minishell");
// }

int	main(int argc, char const *argv[])
{
	char	*prompt;
	int		exit_status;

	(void)argc;
	(void)argv;
	prompt = NULL;
	exit_status = 0;
	while (1)
	{
		prompt = readline("$> ");
		if (prompt == NULL)
			break ;
		if (ft_strlen(prompt) == 0)
			continue ;
		add_history(prompt);
		interpret(prompt, &exit_status);
		free(prompt);
	}
	exit(exit_status);
}
