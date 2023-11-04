/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:48:04 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/04 17:59:57 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

extern sig_atomic_t	g_sig;

/* EBNF
	<program> = <simple_command>
	<simple_command> = <simple_command_element>+
	<simple_command_element> = <redirect>
								| <word>
	<redirect> = <redirect_out>
				| <redirect_in>
				| <redirect_append>
				| <redirect_heredoc>

	<redirect_out> = '>' <word>
	<redirect_in> = '<' <word>
	<redirect_append> = '>>' <word>
	<redirect_heredoc> = '<<' <word>
*/

static int	heredoc_loop(const char *delimiter, int pipe_fd[2])
{
	char	*line;

	line = readline("> ");
	if (line == NULL)
		return (LOOP_END);
	if (g_sig == SIGINT)
	{
		free(line);
		return (LOOP_END);
	}
	if (ft_strlen(line) == ft_strlen(delimiter) && ft_strncmp(line, delimiter,
			ft_strlen(delimiter)) == 0)
	{
		free(line);
		return (LOOP_END);
	}
	ft_dprintf(pipe_fd[1], "%s\n", line);
	free(line);
	return (LOOP_CONTINUE);
}

int	read_heredoc(const char *delimiter)
{
	int		pipe_fd[2];
	int		end_flag;

	if (pipe(pipe_fd) < 0)
		fatal_error("pipe");
	while (1)
	{
		end_flag = heredoc_loop(delimiter, pipe_fd);
		if (end_flag == LOOP_END)
			break ;
	}
	close(pipe_fd[1]);
	if (g_sig == SIGINT)
	{
		close(pipe_fd[0]);
		g_sig = 0;
		return (-1);
	}
	return (pipe_fd[0]);
}

void	operation_file_or_heredoc(t_node *node)
{
	if (node->kind == ND_REDIR_OUT)
		node->file_fd = open(node->filename->word, \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (node->kind == ND_REDIR_IN)
		node->file_fd = open(node->filename->word, O_RDONLY);
	else if (node->kind == ND_REDIR_APPEND)
	{
		printf("append test: %s \n", node->filename->word);
		node->file_fd = open(node->filename->word, \
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else if (node->kind == ND_REDIR_HEREDOC)
		node->file_fd = read_heredoc(node->heredoc->word);
}

static int	node_file_fd_err(t_node *node)
{
	if (node->kind == ND_REDIR_OUT || node->kind == ND_REDIR_APPEND \
		|| node->kind == ND_REDIR_IN)
		xperror(node->filename->word);
	return (-1);
}

int	open_redirect_file(t_node *node)
{
	if (node == NULL)
		return (0);
	if (node->kind == ND_PIPELINE)
	{
		if (open_redirect_file(node->command) < 0)
			return (-1);
		if (open_redirect_file(node->next) < 0)
			return (-1);
		return (0);
	}
	else if (node->kind == ND_SIMPLE_CMD)
		return (open_redirect_file(node->redirects));
	else if (node->kind == ND_REDIR_OUT || node->kind == ND_REDIR_IN \
		|| node->kind == ND_REDIR_APPEND || node->kind == ND_REDIR_HEREDOC)
		operation_file_or_heredoc(node);
	else
		assert_error("open_redirect_file");
	if (node->file_fd < 0)
		return (node_file_fd_err(node));
	node->target_fd_copy = dup(node->target_fd);
	return (open_redirect_file(node->next));
}
