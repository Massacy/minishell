/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:48:04 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/18 05:05:12 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

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

void	do_redirect(t_node *redir)
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

void	reset_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	reset_redirect(redir->next);
	if (is_redirect(redir))
	{
		dup2(redir->target_fd_copy, redir->target_fd);
		close(redir->target_fd_copy);
	}
	else
		assert_error("reset_redirect");
	close(redir->file_fd);
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