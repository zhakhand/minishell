/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:39:05 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/12/20 15:53:13 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*relink_tokens(t_token *empty, t_token *current, t_data *data)
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
	free(empty->val);
	free(empty);
	return current;
}

void	clear_out_es(t_data *data)
{
	t_token	*current;
	t_token	*empty;

	current = data->tokens;
	empty = NULL;
	while (current)
	{
		if (current->type == ES)
		{
			empty = current;
			current = current->next;
			current = relink_tokens(empty, current, data);
		}
		if (current)
			current = current->next;
	}
}

void	join_tokens(t_data *data)
{
	char	*merged;
	t_token	*current;

	current = data->tokens;
	if (!current)
		exit(1);
	while (current)
	{
		if (current->type == WORD && current->next && current->next->type == WORD)
		{
			merged = ft_strjoin(current->val, current->next->val);
			current = relink_tokens(current, current->next, data);
			free(current->val);
			current->val = merged;
		}
		current = current->next;
	}
}

void	merge_tokens(t_data *data)
{
	clear_out_es(data);
	join_tokens(data);
}