/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:43:59 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/06 05:43:33 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_exit(const char *location, const char *msg, int status)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: %s\n", location, msg);
	exit(status);
}

void	tokenize_error(const char *location, char **rest, char *line,
		bool *syntax_error)
{
	*syntax_error = true;
	perror_prefix();
	ft_dprintf(STDERR_FILENO, \
		"syntax error near unexpected character '%c' in %s\n", *line, location);
	while (*line)
		line++;
	*rest = line;
}

void	parse_error(const char *location, t_token **rest, t_token *tok,
		bool *syntax_error)
{
	*syntax_error = true;
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "syntax error near unexpected token '%s' in %s\n",
		tok->word, location);
	while (tok && !at_eof(tok))
		tok = tok->next;
	*rest = tok;
}

void	perror_prefix(void)
{
	ft_dprintf(STDERR_FILENO, "%s", ERROR_PREFIX);
}

void	xperror(const char *location)
{
	perror_prefix();
	perror(location);
}
