#include "../minishell.h"

int	process_input_redirects(t_redir *input_redirects)
{
	if (input_redirects && handle_input_redirects(input_redirects) == -1)
		return (-1);
	return (0);
}

int	process_output_redirects(t_redir *output_redirects)
{
	if (output_redirects && handle_output_redirects(output_redirects) == -1)
		return (-1);
	return (0);
}

int	process_input_list(t_redir *temp, t_redir **in, t_redir **last_input)
{
	if (temp->type == IN || temp->type == HEREDOC)
	{
		if (!(*in))
			*in = temp;
		else
			(*last_input)->next = temp;
		*last_input = temp;
	}
	return (0);
}

int	process_output_list(t_redir *temp, t_redir **out, t_redir **last_output)
{
	if (temp->type == OUT || temp->type == APPEND)
	{
		if (!(*out))
			*out = temp;
		else
			(*last_output)->next = temp;
		*last_output = temp;
	}
	return (0);
}
