/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 06:01:01 by imasayos          #+#    #+#             */
/*   Updated: 2023/09/18 17:45:24 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

#define PATH_MAX 1024

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
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

// 子プロセスで*lineに入っているコマンドを実行する。
int	interpret(char *line)
{
	extern char	**environ;
	char		*argv[] = {line, NULL}; // 今は一つの塊だけ対応。argvは可変長なのでmallocして、そこに引数を入れていく必要がある。
	pid_t		pid;
	int			wstatus;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		// child process
		execve(line, argv, environ);
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
	char **split;
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
		split = ft_split(prompt, ' ');
		add_history(prompt);
		// if (ft_strlen(prompt) == 4 && ft_strncmp(prompt, "exit", 4) == 0)
		// {
		// 	free(prompt);
		// 	free_split(split);
		// 	break;
		// }
		// else if (ft_strlen(split[0]) == 4 && ft_strncmp(split[0], "echo", 4) == 0)
		// {
		// 	if (split[1] == NULL)
		// 		printf("\n");
		// 	else if (ft_strlen(split[1]) == 2 && ft_strncmp(split[1],"-n", 2) == 0)
		// 		if (split[2] == NULL)
		// 			printf("");
		// 		else
		// 			printf("%s", &prompt[7]);
		// 	else
		// 		printf("%s\n", &prompt[5]);
		// }
		// else if (ft_strlen(prompt) == 3 && ft_strncmp(prompt, "pwd", 3) == 0)
		// {
		// 	if (getcwd(path, sizeof(path)) != NULL)
		// 		printf("%s\n", path);
		// 	else
		// 	{
		// 		perror("getcwd() error :");
		// 		return (1);
		// 	}
		// } 
		// else if (ft_strlen(prompt) == 2 && ft_strncmp(prompt, "ls", 2) == 0)
		// {
		// 	interpret("/bin/ls");
		// }
		// else
			// printf("builtin not found: %s\n", prompt);
		char *res;
		res = search_path(prompt);
		if (res)
			exit_status = interpret(res);
		else
		{
			printf("command not found");
			// fatal_error("command not found");
			exit_status = 127;
		}
		free(res);

		free(prompt);
		free_split(split);
	}
	// printf("bye~!\n");
	// return 0;
	exit(exit_status);
}
