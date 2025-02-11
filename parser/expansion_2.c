/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:39:05 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/09 15:42:07 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token *relink_tokens(t_token *empty, t_token *current, t_data *data)
{
	if (current)
	{
		if (!empty->prev)
			data->tokens = current;
		current->prev = NULL;
	}
	empty->next = NULL;
	if (empty->prev)
	{
		empty->prev->next = current;
		if (current)
			current->prev = empty->prev;
	}
	if (empty)
	{
		if (empty->val)
		{
			free(empty->val);
			empty->val = NULL;
		}
		free(empty);
		empty = NULL;
	}
	return current;
}

void clear_out_es(t_data *data)
{
	t_token *current;
	t_token *empty;

	current = data->tokens;
	empty = NULL;
	while (current)
	{
		if (current->type == ES && current->was_quoted == 0)
		{
			empty = current;
			current = current->next;
			current = relink_tokens(empty, current, data);
		}
		else
			current = current->next;
	}
}

void join_tokens(t_data *data)
{
	char *merged;
	t_token *current;

	current = NULL;
	if (!data->tokens)
		exit(1);
	current = data->tokens;
	while (current)
	{
		if ((current->was_quoted || current->type == WORD) && current->next \
		&& (current->next->was_quoted || (current->next->type == WORD || current->next->type == VAR)))
		{
			merged = ft_strjoin(current->val, current->next->val);
			current = relink_tokens(current, current->next, data);
			current->val = merged;
		}
		else
			current = current->next;
	}
}

void merge_tokens(t_data *data)
{
	clear_out_es(data);
	join_tokens(data);
}