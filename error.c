#include "minishell.h"

static void	perror_prefix(void)
{
	dprintf(STDERR_FILENO, "%s", ERROR_PREFIX);
}

void	fatal_error(const char *msg)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "\x1b[31mFatal Error: %s\n\x1b[39m", msg);
	exit(EXIT_FAILURE);
}

void	assert_error(const char *msg)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "assert Error: %s\n", msg);
	exit(255);
}

void	todo(const char *msg)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "TODO: %s\n", msg);
	exit(255);
}

// void command_not_found_error(const char *msg) __attribute__((noreturn));

// void command_not_found_error(const char *cmd)
// {
// 	dprintf(STDERR_FILENO, "\x1b[31mCommand not found: \"%s\" does not found\n\x1b[39m", cmd);
// 	exit(127);
// }

void	err_exit(const char *location, const char *msg, int status)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "%s: %s\n", location, msg);
	exit(status);
}

void	tokenize_error(const char *location, char **rest, char *line, bool *syntax_error)
{
	*syntax_error = true;
	perror_prefix();
	dprintf(STDERR_FILENO, "syntax error near unexpected character '%c' in %s\n", *line, location);
	while (*line)
		line++;
	*rest = line;
}

void	parse_error(const char *location, t_token **rest, t_token *tok, bool *syntax_error)
{
	*syntax_error = true;
	perror_prefix();
	dprintf(STDERR_FILENO, "syntax error near unexpected token '%s' in %s\n", tok->word, location);
	while (tok && !at_eof(tok))
		tok = tok->next;
	*rest = tok;
}

void	xperror(const char *location)
{
	perror_prefix();
	perror(location);
}
