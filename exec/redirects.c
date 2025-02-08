#include "../minishell.h"

extern sig_atomic_t	g_signal;

int	check_directory(char *file)
{
	struct stat	sb;
	char		*temp;
	int			i;

	i = ft_strlen(file);
	while (i > 0)
	{
		if (file[i] == '/')
			break ;
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

int	check_access(char *file)
{
	if (access(file, F_OK) == -1)
	{
		ft_putmsg_fd(MSH, file, N_F_D, STDERR_FILENO);
		return (-1);
	}
	return (0);
}

int	check_redirect(t_redir *redir)
{
	if (redir->type == IN && check_access(redir->val) == -1)
		return (-1);
	else if ((redir->type == OUT || redir->type == APPEND)
		&& check_directory(redir->val) == -1)
		return (-1);
	return (0);
}

int	process_redirects_list(t_redir *temp, t_redir **in, t_redir **out)
{
	t_redir	*last_input;
	t_redir	*last_output;

	last_input = NULL;
	last_output = NULL;
	while (temp)
	{
		if (check_redirect(temp) == -1)
			return (-1);
		process_input_list(temp, in, &last_input);
		process_output_list(temp, out, &last_output);
		temp = temp->next;
	}
	if (last_input)
		last_input->next = NULL;
	if (last_output)
		last_output->next = NULL;
	return (0);
}

int	handle_redirects(t_data *data, t_cmd *node)
{
	t_redir	*input_redirects;
	t_redir	*output_redirects;
	int		err;

	input_redirects = NULL;
	output_redirects = NULL;
	err = 0;
	if (process_redirects_list(node->redir, &in, &out) == -1)
		return (-1);
	if (process_input_redirects(in) == -1)
		return (-1);
	if (process_output_redirects(out) == -1)
		return (-1);
	data->err_no = err;
	return (err);
}
