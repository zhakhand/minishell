/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:42:57 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/26 17:42:57 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include "../minishell.h"

extern sig_atomic_t g_signal;

void ctrl_slash(int signal)
{
	(void)signal;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void ctrl_c_child(int signal)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	g_signal = signal;
}

void ctrl_c(int signal)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_signal = signal;
}

void set_signals(int mode)
{
	if (mode == PARENT)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == CHILD)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, ctrl_slash);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == WAIT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, ctrl_slash);
	}
}