/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_prepare.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:19:54 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 12:19:54 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_input_redirects(t_redir *input_redirects, t_data *data)
{
	if (input_redirects && handle_input_redirects(input_redirects, data) == -1)
		return (-1);
	return (0);
}

int	process_output_redirects(t_redir *output_redirects, t_data *data)
{
	if (output_redirects && handle_output_redirects(output_redirects, data) == -1)
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

int	process_output_list(t_redir *temp, t_redir **out, t_redir **last_out)
{
	if (temp->type == OUT || temp->type == APPEND)
	{
		if (!(*out))
			*out = temp;
		else
			(*last_out)->next = temp;
		*last_out = temp;
	}
	return (0);
}
