
#include "../minishell.h"

extern sig_atomic_t g_signal;

int	handle_in(t_redir *redir)
{
	int	in_fd;

	if (redir->ambig == 1)
	{
		ft_putmsg_fd(MSH, redir->val, AMB, STDERR_FILENO);
		return (-1);
	}
	in_fd = open(redir->val, O_RDONLY);
	if (in_fd == -1)
	{
		ft_putmsg_fd(MSH, redir->val, N_F_D, STDERR_FILENO);
		return (-1);
	}
	if (dup2(in_fd, STDIN_FILENO) == -1)
		return (-1);
	close(in_fd);
	return (0);
}

int	handle_input_redirects(t_redir *redir)
{
	t_redir	*redirects = redir;
	int		in_fd;

	while (redirects)
	{
		if (redirects->type == IN)
		{
			if (handle_in(redirects) == -1)
				return (-1);
		}
		else if (redirects->type == HEREDOC)
		{
			set_signals(HEREDOC);
			in_fd = open(redirects->heredoc, O_RDONLY);
			if (in_fd == -1)
				return (ft_putmsg_fd(MSH, redirects->heredoc, N_F_D, STDERR_FILENO), -1);
			if (dup2(in_fd, STDIN_FILENO) == -1)
				return (-1);
			close(in_fd);
		}
		redirects = redirects->next;
	}
	return (0);
}

int	open_and_close(t_redir *redir)
{
	int	out_fd;

	out_fd = -1;
	if (ft_strcmp(redir->val, "/dev/null") == 0)
		return (0);
	out_fd = open(redir->val, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (out_fd == -1)
		return (ft_putmsg_fd(MSH, redir->val, N_F_D, STDERR_FILENO), -1);
	close(out_fd);
	return (0);
}

int check_directory(char *file)
{
	struct stat sb;
	char *temp;
	int i;

	i = ft_strlen(file);
	while (i > 0)
	{
		if (file[i] == '/')
			break;
		i--;
	}
	if (i == 0)
		temp = ft_strdup(file);
	else
		temp = ft_substr(file, 0, i);
	if (!temp)
		return (-1);
	if (stat(temp, &sb) != 0 && i != 0)
		return (ft_putmsg_fd(MSH, file, N_F_D, STDERR_FILENO), free(temp), -1);
	if (stat(file, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (ft_putmsg_fd(MSH, file, I_A_D, STDERR_FILENO), free(temp), -1);
	free(temp);
	return (0);
}

int handle_out_helper(t_redir *redir)
{
	int out_fd;

	out_fd = -1;
	if (redir->type == OUT)
		out_fd = open(redir->val, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (redir->type == APPEND)
		out_fd = open(redir->val, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (out_fd == -1)
	{
		ft_putmsg_fd(MSH, redir->val, N_F_D, STDERR_FILENO);
		return (-1);
	}
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		return (-1);
	close(out_fd);
	return (0);
}

int	handle_output_redirects(t_redir *redirects)
{
	t_redir	*redir;
	redir = redirects;
	if (check_directory(redirects->val) == -1)
		return (-1);
	while (redir)
	{
		if (redirects->ambig == 1)
			return (ft_putmsg_fd(MSH, redirects->val, AMB, STDERR_FILENO), -1);
		if (redir->next)
		{
			if (open_and_close(redir))
				return (-1);
		}
		else
		{
			if (handle_out_helper(redir) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}

int	check_access(char *file)
{
	if (access(file, F_OK) == -1)
	{
		ft_putmsg_fd(MSH, file, N_F_D, STDERR_FILENO);
		return (-1);
	}
	return (0);
}

int handle_redirects(t_data *data, t_cmd *node)
{
	t_redir *input_redirects = NULL;
	t_redir *output_redirects = NULL;
	t_redir *temp = node->redir;
	t_redir *last_input = NULL;
	t_redir *last_output = NULL;
	int err = 0;

	while (temp)
	{
		if (temp->type == IN && check_access(temp->val) == -1)
			return (-1);
		else if ((temp->type == OUT || temp->type == APPEND) && check_directory(temp->val) == -1)
			return (-1);
		if (temp->type == IN || temp->type == HEREDOC)
		{
			if (!input_redirects)
			{
				input_redirects = temp;
				last_input = temp;
			}
			else
			{
				last_input->next = temp;
				last_input = temp;
			}
		}
		else if (temp->type == OUT || temp->type == APPEND)
		{
			if (!output_redirects)
			{
				output_redirects = temp;
				last_output = temp;
			}
			else
			{
				last_output->next = temp;
				last_output = temp;
			}
		}
		temp = temp->next;
	}
	if (last_input)
		last_input->next = NULL;
	if (last_output)
		last_output->next = NULL;
	if (input_redirects)
		if (handle_input_redirects(input_redirects) == -1)
			return(-1);
	if (output_redirects)
		if (handle_output_redirects(output_redirects) == -1)
			return(-1);
	data->err_no = err;
	return err;
}

