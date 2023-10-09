/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 07:30:51 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/09 15:21:02 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_sig = 0;

/*   
	入力の偽装
    TIOCSTI   const char *argp
    指定されたバイトを入力キューに挿入する。
*/

void	handler(int signum)
{
	g_sig = signum;
	// printf("handler: %d\n", signum);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	reset_sig(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	if (sigaction(signum, &sa, NULL) < 0)
		fatal_error("sigaction");
}

void	ignore_sig(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	if (sigaction(signum, &sa, NULL) < 0)
		fatal_error("sigaction");
}

void	setup_sigint(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		fatal_error("sigaction");
}

// readline中かつSIGINTの時に、readのバッファを消してread終了にする。
// int	check_state(void)
// {
// 	if (sig == 0)
// 		return (0);
// 	else if (sig == SIGINT)
// 	{
// 		sig = 0;
// 		*signal_interrupt = true;
// 		rl_replace_line("", 0);
// 		rl_done = 1;
// 		return (0);
// 	}
// 	return (0);
// }

// https://tiswww.case.edu/php/chet/readline/readline.html
void	setup_signal(void)
{
	// extern int	_rl_echo_control_chars; // ←これ何

	// _rl_echo_control_chars = 0;
	// rl_outstream = stderr; // rlの出力先を設定
	// if (isatty(STDIN_FILENO))
	// 	rl_event_hook = check_state; // rlがread中に何も入力されないと1秒間に10回以上定期的に呼ぶ関数を設定
	ignore_sig(SIGQUIT);
	setup_sigint();
}

void	reset_signal(void)
{
	reset_sig(SIGQUIT);
	reset_sig(SIGINT);
}
