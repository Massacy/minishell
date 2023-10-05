/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 05:06:00 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/06 06:38:20 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parse(t_token *tok, bool *syntax_error)
{
	return (parse_pipeline(&tok, tok, syntax_error));
}

// inpipe[0] = left's in
// outpipe[1] = right's out
t_node	*parse_pipeline(t_token **rest, t_token *tok, bool *syntax_error)
{
	t_node	*node;

	node = new_node(ND_PIPELINE);
	node->inpipe[0] = STDIN_FILENO;
	node->inpipe[1] = -1;
	node->outpipe[0] = -1;
	node->outpipe[1] = STDOUT_FILENO;
	node->command = simple_command(&tok, tok, syntax_error);
	if (equal_op(tok, "|"))
		node->next = parse_pipeline(&tok, tok->next, syntax_error);
	*rest = tok;
	return (node);
}

t_node	*simple_command(t_token **rest, t_token *tok, bool *syntax_error)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_CMD);
	while (tok && !at_eof(tok) && !is_control_operator(tok))
		append_cmd_elem(node, &tok, tok, syntax_error);
	*rest = tok;
	return (node);
}

// append_cmd_elem -> parse_error("Unexpected Token", &tok, tok, syntax_error);
void	append_cmd_elem(t_node *cmd, t_token **rest, t_token *tok,
		bool *syntax_error)
{
	if (is_word_tok(tok))
	{
		append_tok(&cmd->args, tokdup(tok));
		tok = tok->next;
	}
	else if (equal_op(tok, ">") && is_word_tok(tok->next))
		append_node(&cmd->redirects, redirect_ioah(&tok, tok, ND_REDIR_OUT,
				STDOUT_FILENO));
	else if (equal_op(tok, "<") && is_word_tok(tok->next))
		append_node(&cmd->redirects, redirect_ioah(&tok, tok, ND_REDIR_IN,
				STDIN_FILENO));
	else if (equal_op(tok, ">>") && is_word_tok(tok->next))
		append_node(&cmd->redirects, redirect_ioah(&tok, tok, ND_REDIR_APPEND,
				STDOUT_FILENO));
	else if (equal_op(tok, "<<") && is_word_tok(tok->next))
		append_node(&cmd->redirects, redirect_ioah(&tok, tok, ND_REDIR_HEREDOC,
				STDIN_FILENO));
	else
		todo("append_cmd_elem");
	(void)syntax_error;
	*rest = tok;
}

// redirect [in/out/append/heredoc]
// !! parameter kind must be ND_REDIR_* !!
t_node	*redirect_ioah(t_token **rest, t_token *tok, t_node_kind kind,
		int target_fd)
{
	t_node	*node;

	node = new_node(kind);
	if (kind == ND_REDIR_HEREDOC)
		node->heredoc = tokdup(tok->next);
	else
		node->filename = tokdup(tok->next);
	node->target_fd = target_fd;
	*rest = tok->next->next;
	return (node);
}
