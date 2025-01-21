/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:40:06 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/21 15:25:01 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	check_redirs(t_data *data)
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

	current = NULL;
	if (data->tokens)
		current = data->tokens;
	while (current)
	{
		if (current && current->type == PIPE)
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

void	syntax_check(t_data *data)
{
	t_token *curr;

	curr = data->tokens;
	while (curr)
	{
		if (curr->was_quoted && ft_strlen(curr->val) == 0)
		{
			if (curr->next && curr->next->type == PIPE)
				error_msg(CMD_NOT_FOUND, curr, data);
		}
		curr = curr->next;
	}
}