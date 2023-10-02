/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:48:04 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/03 08:24:16 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

#include <fcntl.h>


int	read_heredoc(const char *delimiter)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		fatal_error("pipe");
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		dprintf(pipe_fd[1], "%s\n", line);
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
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
	else if (node->kind == ND_REDIR_OUT)
		node->file_fd = open(node->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (node->kind == ND_REDIR_IN)
		node->file_fd = open(node->filename->word, O_RDONLY);
	else if (node->kind == ND_REDIR_APPEND)
		node->file_fd = open(node->filename->word, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (node->kind == ND_REDIR_HEREDOC)
		node->file_fd = read_heredoc(node->heredoc->word);
	else
		assert_error("open_redirect_file");
	if (node->file_fd < 0)
	{
		xperror(node->filename->word);
		return (-1);
	}
	node->target_fd_copy = dup(node->target_fd);
	return (open_redirect_file(node->next));
}

bool	is_redirect(t_node *node)
{
	if (node->kind == ND_REDIR_OUT)
		return (true);
	else if (node->kind == ND_REDIR_IN)
		return (true);
	else if (node->kind == ND_REDIR_APPEND)
		return (true);
	else if (node->kind == ND_REDIR_HEREDOC)
		return (true);
	return (false);
}

void do_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	if (is_redirect(redir))
	{
		dup2(redir->file_fd, redir->target_fd);
 		close(redir->file_fd);
	}
	else
		assert_error("do_redirect");
	do_redirect(redir->next);
}


void reset_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
		
	reset_redirect(redir->next);
	if (is_redirect(redir))
		dup2(redir->target_fd_copy, redir->target_fd);
	else
		assert_error("reset_redirect");
}

// void redirect(int target_fd, char *filename)
//  {
// 	int file_fd;
// 	int target_fd_copy;

// 	target_fd_copy = dup(target_fd);
// 	file_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
 
//      // // dup2使わないバージョン
//      // close(targetfd);    // 1を閉じる
//      // dup(filefd);        // 1にfilefdを持ってくる
//      // close(filefd);      // filefdはいらない
//  	dup2(file_fd, target_fd);
//  	close(file_fd);
 
//  	exec_command();
 
//      // // dup2使わないバージョン
//      // close(targetfd);
//      // dup(stashed_targetfd);
//      // close(stashed_targetfd);
//  	dup2(target_fd_copy, target_fd);
//  }



