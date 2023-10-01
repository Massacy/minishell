/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 06:01:01 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/01 17:54:00 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int free_split(char **split)
{
	int i;

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
// char **token_list_to_argv(t_token *tok)
// {
// 	char **argv;
// 	int cnt;
// 	int i;
// 	t_token *cur;

// 	cnt = 0;
// 	cur = tok;
// 	while (cur->word != NULL)
// 	{
// 		cnt++;
// 		cur = cur->next;
// 	}
// 	argv = calloc(cnt + 1, sizeof(char *));
// 	if (argv == NULL)
// 		fatal_error("calloc");
	
// 	cur = tok;
// 	i = -1;
// 	while(++i < cnt)
// 	{
// 		argv[i] = cur->word;
// 		cur = cur->next;
// 	}
// 	argv[i] = NULL;
// 	return (argv);
// }

// TODO あとで、↑と↓の違いをみておく。

char	**tail_recursive(t_token *tok, int nargs, char **argv)
{
	if (tok == NULL || tok->kind == TK_EOF)
		return (argv);
	argv = reallocf(argv, (nargs + 2) * sizeof(char *));
	argv[nargs] = strdup(tok->word);
	if (argv[nargs] == NULL)
		fatal_error("strdup");
	argv[nargs + 1] = NULL;
	return (tail_recursive(tok->next, nargs + 1, argv));
}

char	**token_list_to_argv(t_token *tok)
{
	char	**argv;

	argv = calloc(1, sizeof(char *));
	if (argv == NULL)
		fatal_error("calloc");
	return (tail_recursive(tok, 0, argv));
}

void echo_args(char **split)
{
	int i;

	i = 0;
	while (split[i] != NULL)
	{
		printf("%s", split[i]);
		if (split[i+1] != NULL)
			printf(" ");
		i++;
	}
}

void exec_built_in(char **split)
{
	// printf("[test start]------exec_built_in------\n");
	// int i;
	// i = 0;
	// while (split[i] != NULL)
	// {
	// 	printf("%s\n", split[i]);
	// 	i++;
	// }
	// printf("[test end]------exec_built_in------\n");
	
	if (split[0] != NULL)
	{
		if (ft_strlen(split[0]) == 4 && ft_strncmp(split[0], "echo", 4) == 0)
		{
			if (split[1] == NULL)
				printf("\n");
			else if (ft_strlen(split[1]) == 2 && ft_strncmp(split[1],"-n", 2) == 0)
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

int	exec(char *argv[])
{
	extern char	**environ;
	const char	*path = argv[0];
	pid_t		pid;
	int			wstatus;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		// child process
		if (strchr(path, '/') == NULL)
			path = search_path(path);
		validate_access(path, argv[0]);
		execve(path, argv, environ);
		fatal_error("execve");
	}
	else
	{
		// parent process
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}

// 子プロセスで*lineに入っているコマンドを実行する。
void	interpret(char *line, int *stat_loc)
{
	t_token		*tok;
	char **argv;
	t_node *node;
	bool syntax_error;
	// char		*argv[] = {line, NULL}; // 今は一つの塊だけ対応。argvは可変長なのでmallocして、そこに引数を入れていく必要がある。
	// pid_t		pid;
	// int			wstatus;
	syntax_error = false;

	tok = tokenize(line, &syntax_error);
	if (tok->kind == TK_EOF)
		;
	else if(syntax_error)
		*stat_loc = ERROR_TOKENIZE;
	else
	{
		node = parse(tok, &syntax_error);
		if (syntax_error)
			*stat_loc = ERROR_PARSE;
		else
		{
			expand(node);
			argv = token_list_to_argv(node->args);
			*stat_loc = exec(argv);
			free_argv(argv);
		}
		free_node(node);
	}
	free_tok(tok);
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
		bzero(path, PATH_MAX);
		end = strchr(value, ':');
		if (end)
			strncpy(path, value, end - value); // 要修正
		else
			strlcpy(path, value, PATH_MAX); // 要修正
		strlcat(path, "/", PATH_MAX);
		strlcat(path, filename, PATH_MAX);
		if (access(path, X_OK) == 0)
		{
			char	*dup;

			dup = strdup(path);
			if (dup == NULL)
				fatal_error("strdup");
			return (dup);
		}
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

int main(int argc, char const *argv[])
{
	char *prompt;
	// char **split;
	// char path[1024];
	int exit_status;
	
	(void)argc;
	(void)argv;
	prompt = NULL;
	exit_status = 0;
	while (1)
	{
		prompt = readline("$> ");
		if (prompt == NULL)
			break;
		if (ft_strlen(prompt) == 0)
			continue;

		add_history(prompt);

		interpret(prompt, &exit_status);
		// debug : printf("exit_status : %d\n", exit_status);
		// res = search_path(tok->word); // 一旦先頭のtokのみ実行。
		free(prompt);
	}
	// printf("bye~!\n");
	// return 0;
	exit(exit_status);
}
