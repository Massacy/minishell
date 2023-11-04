/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:37:18 by imasayos          #+#    #+#             */
/*   Updated: 2023/11/04 21:18:03 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	・ひとつでもblankを進めたらがあればtrueを返して、そうでなければfalseを返す。
	・blankがあるとき、'\0'かblankでない文字になるまでポインタを進めて、restに代入する。
	・restはlineのポインタを指しているので、呼び出し元でのlineのポインタの位置が変わる。
*/
bool	consume_blank(char **rest, char *line)
{
	if (is_blank(*line))
	{
		while (*line != '\0' && is_blank(*line))
			line++;
		*rest = line;
		return (true);
	}
	*rest = line;
	return (false);
}

static const char	*g_operators[] = {">>", "<<", "||", "&&", ";;", "<", ">",
	"&", ";", "(", ")", "|", "\n"};

t_token	*operator(char **rest, char *line)
{
	size_t	i;
	char	*op;

	i = 0;
	while (i < sizeof(g_operators) / sizeof(*g_operators))
	{
		if (startswith(line, g_operators[i]))
		{
			op = ft_strdup(g_operators[i]);
			if (op == NULL)
				fatal_error("strdup");
			*rest = line + ft_strlen(op);
			return (new_token(op, TK_OP));
		}
		i++;
	}
	assert_error("Unexpected operator");
	return (NULL);
}

static char	*quote_check(char *line, const char c, char *msg,
		bool *syntax_error)
{
	line++;
	while (*line != c)
	{
		if (*line == '\0')
		{
			tokenize_error(msg, &line, line, syntax_error);
			return (line);
		}
		line++;
	}
	line++;
	return (line);
}

t_token	*word(char **rest, char *line, bool *syntax_error)
{
	const char	*start;
	char		*word;

	start = line;
	while (*line != '\0' && !is_metacharacter(*line))
	{
		if (*line == SINGLE_QUOTE_CHAR)
			line = quote_check(line, SINGLE_QUOTE_CHAR, "Unclosed single quote",
					syntax_error);
		else if (*line == DOUBLE_QUOTE_CHAR)
			line = quote_check(line, DOUBLE_QUOTE_CHAR, "Unclosed double quote",
					syntax_error);
		else
			line++;
	}
	word = ft_strndup(start, line - start);
	if (word == NULL)
		fatal_error("strndup");
	*rest = line;
	return (new_token(word, TK_WORD));
}

/*
	headはdummyで、head.nextが最初のtokenを指している。
	operatorとwordをtokにつなげていく。
*/
t_token	*tokenize(char *line, bool *syntax_error)
{
	t_token	head;
	t_token	*tok;

	head.next = NULL;
	tok = &head;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		else if (is_metacharacter(*line))
			tok->next = operator(&line, line);
		else if (is_word(line))
			tok->next = word(&line, line, syntax_error);
		else
			tokenize_error("Unexpected Token", &line, line, syntax_error);
		tok = tok->next;
	}
	tok->next = new_token(NULL, TK_EOF);
	return (head.next);
}
