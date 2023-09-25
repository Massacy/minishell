#include "minishell.h"



void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "\x1b[31mFatal Error: %s\n\x1b[39m", msg);
	exit(EXIT_FAILURE);
}

void	assert_error(const char *msg)
{
	dprintf(STDERR_FILENO, "assert Error: %s\n", msg);
	exit(255);
}

void	todo(const char *msg)
{
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
	dprintf(STDERR_FILENO, "minishell: %s: %s\n", location, msg);
	exit(status);
}