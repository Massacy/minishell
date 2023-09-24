/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 06:01:01 by imasayos          #+#    #+#             */
/*   Updated: 2023/09/23 18:47:05 by imasayos         ###   ########.fr       */
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

void	fatal_error(const char *msg) __attribute__((noreturn));

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "\x1b[31m");
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	dprintf(STDERR_FILENO, "\x1b[39m");
	exit(EXIT_FAILURE);
}

void command_not_found_error(const char *msg) __attribute__((noreturn));

void command_not_found_error(const char *cmd)
{
	dprintf(STDERR_FILENO, "\x1b[31m");
	dprintf(STDERR_FILENO, "Command not found: \"%s\" does not found\n", cmd);
	dprintf(STDERR_FILENO, "\x1b[39m");
	exit(127);
}


/*
	t_tokenの線形リストをchar**に変換する。
	・線形リストの要素数を数える。
	・char**をcallocで確保する。
	・線形リストを順番に回して、char**にwordをコピーしていく。
	・char**の最後にNULLを入れる。
	※ wordは線形リスト内のポインタを指しているので、このargv使用中はtokをfreeしてはいけない。
*/
char **token_list_to_argv(t_token *tok)
{
	char **argv;
	int cnt;
	int i;
	t_token *cur;

	cnt = 0;
	cur = tok;
	while (cur->word != NULL)
	{
		cnt++;
		cur = cur->next;
	}
	argv = calloc(cnt + 1, sizeof(char *));
	if (argv == NULL)
		fatal_error("calloc");
	
	cur = tok;
	i = -1;
	while(++i < cnt)
	{
		argv[i] = cur->word;
		cur = cur->next;
	}
	argv[i] = NULL;
	return (argv);
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

// 子プロセスで*lineに入っているコマンドを実行する。
// int	interpret(char *line)
int	interpret(t_token *tok)
{
	extern char	**environ;
	// t_token		*tok;
	char **argv;	
	// char		*argv[] = {line, NULL}; // 今は一つの塊だけ対応。argvは可変長なのでmallocして、そこに引数を入れていく必要がある。
	pid_t		pid;
	int			wstatus;

	argv = token_list_to_argv(tok);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		// child process
		// execve(line, argv, environ);
		char *res;
		res = search_path(argv[0]);
		if (res)
			execve(res, argv, environ);
		else
			command_not_found_error(argv[0]);
		fatal_error("execve");
	}
	else
	{
		// parent process
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
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
		// split = ft_split(prompt, ' '); -> tokenizeする。
		add_history(prompt);
		// char *res;
		// char *line;
		t_token *tok;

		tok = tokenize(prompt);
		exit_status = interpret(tok);
		// debug : printf("exit_status : %d\n", exit_status);
		// res = search_path(tok->word); // 一旦先頭のtokのみ実行。

		// // exit_status = interpret(prompt);

		// res = search_path(prompt);
		// if (res)
		// 	exit_status = interpret(tok);
		// else
		// {
		// 	printf("command not found\n");
		// 	exit_status = 127;
		// }
		// free(res);

		free(prompt);
		// free_split(split);
	}
	// printf("bye~!\n");
	// return 0;
	exit(exit_status);
}
