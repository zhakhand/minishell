/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:40:06 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/27 12:38:42 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	check_redirs(t_data *data)
{
	t_token	*current;

	current = NULL;
	if (data->tokens)
		current = data->tokens;
	while (current)
	{
		if (is_redir(current->type))
		{
			if (current->next && is_redir(current->next->type))
				return (error_msg(UNEXPECTED_TOKEN, current->next, data));
			else if (!current->next)
				return (error_msg(UNEXPECTED_TOKEN, NULL, data));
		}
		current = current->next;
	}
	return (0);
}

int	check_pipes(t_data *data)
{
	t_token	*current;

	current = NULL;
	if (data->tokens)
		current = data->tokens;
	while (current)
	{
		if (current && current->type == PIPE)
		{
			if (pipe_check(data, current) != 0)
				return (ERROR);
		}
		current = current->next;
	}
	return (0);
}

void	delete_spaces(t_data *data)
{
	t_token	*current;

	current = NULL;
	if (data->tokens)
		current = data->tokens;
	while (current)
	{
		if (current->type == WS && current->was_quoted == 0)
			current = relink_tokens(current, current->next, data);
		else
			current = current->next;
	}
}
