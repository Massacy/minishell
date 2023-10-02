/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:37:18 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/03 08:35:36 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*tok;

	tok = calloc(1, sizeof(*tok));
	if (tok == NULL)
		fatal_error("calloc");
	tok->word = word;
	tok->kind = kind;
	return (tok);
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

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

/*
	sの先頭からkeywordであるか比較して一致すればtrueを返す。
*/
bool	startswith(const char *s, const char *keyword)
{
	return (memcmp(s, keyword, strlen(keyword)) == 0);
}


/*
	metacharacter
		A character that, when unquoted, separates words.  One of the following:
		|  & ; ( ) < > space tab
*/
bool	is_metacharacter(char c)
{
	if (is_blank(c))
		return (true);
	return (c && strchr("|&;()<>\n", c));
}

/*
	metacharacterでない文字をwordとして扱う。
*/
bool	is_word(const char *s)
{
	return (*s && !is_metacharacter(*s));
}

t_token	*operator(char **rest, char *line)
{
	size_t	i;
	char	*op;

	// static char *const operators[] = {"||", "&", "&&", ";", ";;", "(", ")",
	//	"|", "\n"};
	static char *const operators[] = {">>", "<<", "||", "&&", ";;", "<", ">",
		"&", ";", "(", ")", "|", "\n"};
	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(line, operators[i]))
		{
			op = strdup(operators[i]);
			if (op == NULL)
				fatal_error("strdup");
			*rest = line + strlen(op);
			return (new_token(op, TK_OP));
		}
		i++;
	}
	assert_error("Unexpected operator");
	return (NULL); // unreachable
}

t_token	*word(char **rest, char *line)
{
	const char	*start;
	char		*word;

	start = line;
	while (*line != '\0' && !is_metacharacter(*line))
	{
		if (*line == SINGLE_QUOTE_CHAR)
		{
			// skip single quote
			line++;
			while (*line != SINGLE_QUOTE_CHAR)
			{
				if (*line == '\0')
					todo("Unclosed single quote");
				line++;
			}
			// skip single quote
			line++;
		}
		else if (*line == DOUBLE_QUOTE_CHAR)
		{
			// skip double quote
			line++;
			while (*line != DOUBLE_QUOTE_CHAR)
			{
				if (*line == '\0')
					todo("Unclosed double quote");
				line++;
			}
			// skip double quote
			line++;
		}
		else
			line++;
	}
	word = strndup(start, line - start);
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
			tok = tok->next = operator(&line, line);
		else if (is_word(line))
			tok = tok->next = word(&line, line);
		else
			tokenize_error("Unexpected Token", &line, line, syntax_error);
	}
	tok->next = new_token(NULL, TK_EOF);
	return (head.next);
}
