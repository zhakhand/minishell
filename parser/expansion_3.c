/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:40:06 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/09 14:48:17 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	check_redirs(t_data *data)
{
	t_token	*current;

	if (!data->tokens)
		exit(1);
	current = data->tokens;
	while (current)
	{
		if (is_redir(current->type))
		{
			if (current->next && is_redir(current->next->type))
				error_msg(UNEXPECTED_TOKEN, current->next, data);
			else if (!current->next)
				error_msg(UNEXPECTED_TOKEN, NULL, data);
		}
		current = current->next;
	}
}

void check_pipes(t_data *data)
{
	t_token *current;

	if (!data->tokens)
		exit(1);
	current = data->tokens;
	while (current)
	{
		if (current->type == PIPE)
		{
			if (!current->prev)
				error_msg(UNEXPECTED_TOKEN, current, data);
			if (current->next)
			{
				if (current->next->type == PIPE)
					error_msg(UNEXPECTED_TOKEN, current->next, data);
			}
			else
				error_msg(UNEXPECTED_TOKEN, NULL, data);
		}
		current = current->next;
	}
}

void delete_spaces(t_data *data)
{
	t_token *current;

	if (!data->tokens)
		exit(1);
	current = data->tokens;
	while (current)
	{
		if (current->type == WS && current->was_quoted == 0)
			current = relink_tokens(current, current->next, data);
		else
			current = current->next;
	}
}