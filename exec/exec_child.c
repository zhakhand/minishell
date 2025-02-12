#include "../minishell.h"
#include "../parser.h"
#include <unistd.h>

void	clean_child(t_data *data, int fds[2])
{
	if (fds[0] != STDIN_FILENO)
		close(fds[0]);
	if (fds[1] != STDOUT_FILENO)
		close(fds[1]);
	clean_data(data);
}

void	check_redirects(t_data *data, t_cmd *cmd)
{
	if (handle_redirects(data, cmd) == -1)
	{
		data->err_no = 1;
		data->redir_err = 1;
	}
}

int	if_was_redir(t_cmd *cmd)
{
	if (cmd->redir && (cmd->redir->type == OUT || cmd->redir->type == APPEND))
		return (1);
	return (0);
}

int	set_child_err(t_data *data, t_cmd *cmd)
{
	int	err;

	err = data->err_no;
	clean_child(data, cmd->fds);
	return (err);
}

void	run_child(t_data *data, t_cmd *cmd, char **envp, int prev_fd)
{
	int	check_redir;

	set_signals(CHILD);
	if (prev_fd != STDIN_FILENO)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			panic("dup2 prev_fd");
		close(prev_fd);
	}
	check_redirects(data, cmd);
	check_redir = if_was_redir(cmd);
	if (cmd->next != NULL && !check_redir)
	{
		close(cmd->fds[0]);
		if (dup2(cmd->fds[1], STDOUT_FILENO) == -1)
			panic("dup2 fds[1]");
		close(cmd->fds[1]);
	}
	if (!check_child_buildin(cmd) && data->redir_err == 0)
		data->err_no = exec_buildin(data, cmd);
	else if (data->redir_err == 0
		&& !ft_edge_cases(data, cmd) && check_child_buildin(cmd) == 1)
		data->err_no = run_execve(data, cmd, envp);
	exit(set_child_err(data, cmd));
}
