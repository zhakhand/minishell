/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:19:26 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 12:19:26 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parser.h"
#include <unistd.h>

extern sig_atomic_t	g_signal;

int	close_fds_parent(int prev_fd, t_cmd *cmd)
{
	if (prev_fd != STDIN_FILENO)
		close(prev_fd);
	prev_fd = cmd->fds[0];
	if (cmd->next != NULL)
	{
		close(cmd->fds[1]);
		prev_fd = cmd->fds[0];
	}
	return (prev_fd);
}

void	parent_wait_child(t_data *data)
{
	int	status;

	set_signals(WAIT);
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			data->err_no = WEXITSTATUS(status);
	}
}

int	init_parent_vars(t_data *data, t_cmd *cmd)
{
	int	prev_fd;

	data->child_start = 0;
	cmd->fds[0] = STDIN_FILENO;
	cmd->fds[1] = STDOUT_FILENO;
	prev_fd = STDIN_FILENO;
	if (cmd->next != NULL)
		data->we_have_child = 1;
	return (prev_fd);
}

pid_t	make_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		panic("fork err");
	return (pid);
}

int	run_pipe(t_data *data, t_cmd *cmd, char **envp)
{
	data->prev_fd = init_parent_vars(data, cmd);
	while (cmd != NULL)
	{
		data->redir_err = 0;
		if (!check_parent_buildin(cmd))
		{
			data->err_no = exec_buildin(data, cmd);
			if (cmd->next == NULL)
			{
				if (data->prev_fd != STDIN_FILENO)
					close(data->prev_fd);
				return (0);
			}
		}
		if (cmd->next != NULL && pipe(cmd->fds) == -1)
			panic("pipe err");
		data->child_start = 1;
		data->pid = make_fork();
		if (data->pid == 0)
			run_child(data, cmd, envp, data->prev_fd);
		data->prev_fd = close_fds_parent(data->prev_fd, cmd);
		cmd = cmd->next;
	}
	parent_wait_child(data);
	return (0);
}
