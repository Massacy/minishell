/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:48:04 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/02 06:37:35 by imasayos         ###   ########.fr       */
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

int	open_redirect_file(t_node *redir)
{
	if (redir == NULL)
		return (0);
	if (redir->kind == ND_REDIR_OUT)
		redir->file_fd = open(redir->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->kind == ND_REDIR_IN)
		redir->file_fd = open(redir->filename->word, O_RDONLY);
	// else if (redir->kind == ND_REDIR_APPEND)
	// 	redir->file_fd = open(redir->filename->word, O_CREAT | O_WRONLY | O_APPEND, 0644);
	// else if (redir->kind == ND_REDIR_HEREDOC)
	// 	redir->file_fd = open(redir->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// else
	// 	fatal_error("open_redirect_file");
	if (redir->file_fd < 0)
	{
		xperror(redir->filename->word);
		return (-1);
	}
	redir->target_fd_copy = dup(redir->target_fd);
	return (open_redirect_file(redir->next));
}


void do_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	if (redir->kind == ND_REDIR_OUT || redir->kind == ND_REDIR_IN)
	{
		dup2(redir->file_fd, redir->target_fd);
 		close(redir->file_fd);
	}
	else
		todo("do_redirect");
	do_redirect(redir->next);
}


void reset_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
		
	reset_redirect(redir->next);
	if (redir->kind == ND_REDIR_OUT || redir->kind == ND_REDIR_IN)
		dup2(redir->target_fd_copy, redir->target_fd);
	else
		todo("reset_redirect");
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



