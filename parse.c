#include "minishell.h"



bool	at_eof(t_token *tok)
{
	return (tok->kind == TK_EOF);
}

bool	equal_op(t_token *tok, char *op)
{
	if (tok->kind != TK_OP)
		return (false);
	return (strcmp(tok->word, op) == 0);
}

bool is_word_tok(t_token *tok)
{
	return (tok->kind == TK_WORD);
}

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = calloc(1, sizeof(*node));
	if (node == NULL)
		fatal_error("calloc");
	node->kind = kind;
	return (node);
}

t_token	*tokdup(t_token *tok)
{
	char	*word;

	word = strdup(tok->word);
	if (word == NULL)
		fatal_error("strdup");
	return (new_token(word, tok->kind));
}

/*
	tokの末尾にelemを追加する。
*/
void	append_tok(t_token **tok, t_token *elem)
{
	if (*tok == NULL)
	{
		*tok = elem;
		return ;
	}
	append_tok(&(*tok)->next, elem);
}

void	append_node(t_node **node, t_node *elem)
{
	if (*node == NULL)
	{
		*node = elem;
		return ;
	}
	append_node(&(*node)->next, elem);
}


t_node	*pipeline(t_token **rest, t_token *tok, bool *syntax_error)
{
	t_node	*node;

	node = new_node(ND_PIPELINE);
	node->inpipe[0] = STDIN_FILENO; // 左のin
	node->inpipe[1] = -1;
	node->outpipe[0] = -1;
	node->outpipe[1] = STDOUT_FILENO; //左のout
	node->command = simple_command(&tok, tok, syntax_error);
	if (equal_op(tok, "|"))
		node->next = pipeline(&tok, tok->next, syntax_error);
	*rest = tok;
	return (node);
}

t_node	*parse(t_token *tok, bool *syntax_error)
{
	return (pipeline(&tok, tok, syntax_error));
}

bool	is_control_operator(t_token *tok)
{
	static char	*const	operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t				i = 0;

	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(tok->word, operators[i]))
			return (true);
		i++;
	}
	return (false);
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

t_node	*redirect_out(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_OUT);
	node->filename = tokdup(tok->next);
	node->target_fd = STDOUT_FILENO;
	*rest = tok->next->next;
	return (node);
}

t_node	*redirect_in(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_IN);
	node->filename = tokdup(tok->next);
	node->target_fd = STDIN_FILENO;
	*rest = tok->next->next;
	return (node);
}

t_node *redirect_append(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_APPEND);
	node->filename = tokdup(tok->next);
	node->target_fd = STDOUT_FILENO;
	*rest = tok->next->next;
	return (node);
}

t_node	*redirect_heredoc(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_HEREDOC);
	node->heredoc = tokdup(tok->next);
	node->target_fd = STDIN_FILENO;
	*rest = tok->next->next;
	return (node);
}

void append_cmd_elem(t_node *cmd, t_token **rest, t_token *tok, bool *syntax_error)
{

	if (is_word_tok(tok))
	{
		append_tok(&cmd->args, tokdup(tok));
		tok = tok->next;
	}
	else if (equal_op(tok, ">") && is_word_tok(tok->next))
		append_node(&cmd->redirects, redirect_out(&tok, tok));
	else if (equal_op(tok, "<") && is_word_tok(tok->next))
		append_node(&cmd->redirects, redirect_in(&tok, tok));
	else if (equal_op(tok, ">>") && is_word_tok(tok->next))
		append_node(&cmd->redirects, redirect_append(&tok, tok));
	else if (equal_op(tok, "<<") && is_word_tok(tok->next))
		append_node(&cmd->redirects, redirect_heredoc(&tok, tok));
	else
		todo("append_cmd_elem");
		
		// parse_error("Unexpected Token", &tok, tok, syntax_error);
	(void)syntax_error;
	*rest = tok;
}