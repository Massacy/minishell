#include <stdlib.h>
#include "minishell.h"

#include <string.h>

void	append_char(char **s, char c)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s)
		size += strlen(*s);
	new = malloc(size);
	if (new == NULL)
		fatal_error("malloc");
	if (*s)
		strlcpy(new, *s, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

void	quote_removal(t_token *tok)
{
	char	*new_word;
	char	*p;

	if (tok == NULL || tok->kind != TK_WORD || tok->word == NULL)
		return ;
	p = tok->word;
	new_word = NULL;
	// int sq = 0;
	// int dq = 0;

	while (*p && !is_metacharacter(*p))
	{
		// if (*p == SINGLE_QUOTE_CHAR || *p == DOUBLE_QUOTE_CHAR)
		// {
		// 	if (*p == SINGLE_QUOTE_CHAR)
		// 		sq++;
		// 	else if (*p == DOUBLE_QUOTE_CHAR)
		// 		dq++;
		// 	p++;
		// }
		// else if (*p == '\0' && (sq%2 == 1 || dq%2 == 1)) // TODO 欠陥あるので直す
		// {
		// 	printf("todo : Unclosed single quote\n");
		// 	break;
		// }
		// else
		// 	append_char(&new_word, *p++);

		if (*p == SINGLE_QUOTE_CHAR)
		{
			// skip quote
			p++;
			while (*p != SINGLE_QUOTE_CHAR)
			{
				if (*p == '\0')
				{
					printf("todo : Unclosed single quote\n");
					break;
				}
				append_char(&new_word, *p++);
			}
			// skip quote
			if (*p != '\0')
				p++;
		}
		// else if (*p == DOUBLE_QUOTE_CHAR)
		// {
		// 	// skip quote
		// 	p++;
		// 	while (*p != DOUBLE_QUOTE_CHAR)
		// 	{
		// 		if (*p == '\0')
		// 		{
		// 			printf("todo : Unclosed double quote\n");
		// 			break;
		// 		}
		// 		append_char(&new_word, *p++);
		// 	}
		// 	// skip quote
		// 	if (*p != '\0')
		// 		p++;
		// }
		else
			append_char(&new_word, *p++);
	}
	free(tok->word);
	tok->word = new_word;
	quote_removal(tok->next);
}

void	expand(t_token *tok)
{
	quote_removal(tok);
}