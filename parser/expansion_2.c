/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:39:05 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/27 12:37:59 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	check_current(t_token *empty, t_token *current, t_data *data)
{
	if (current)
	{
		if (!empty->prev)
			data->tokens = current;
		current->prev = NULL;
	}
	else
	{
		if (!empty->prev)
			data->tokens = NULL;
	}
}

t_token	*relink_tokens(t_token *empty, t_token *current, t_data *data)
{
	check_current(empty, current, data);
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
		if (empty)
			free(empty);
		empty = NULL;
	}
	return (current);
}

void	clear_out_es(t_data *data)
{
	t_token	*current;
	t_token	*empty;

	current = data->tokens;
	empty = NULL;
	while (current)
	{
		if ((current->type == ES) && current->was_quoted == 0)
		{
			empty = current;
			current = current->next;
			current = relink_tokens(empty, current, data);
		}
		else
			current = current->next;
	}
}

void	join_tokens(t_data *data)
{
	char	*merged;
	t_token	*c;

	c = NULL;
	if (data->tokens)
		c = data->tokens;
	while (c)
	{
		if (c->touches_next == 1 && c->next)
		{
			if (c->is_delim && (c->was_quoted != 0 || c->next->was_quoted != 0))
			{
				c->was_quoted = 2;
				c->next->was_quoted = 2;
			}
			merged = ft_strjoin(c->val, c->next->val);
			if (!merged)
				end_it(data);
			c = relink_tokens(c, c->next, data);
			free(c->val);
			c->val = merged;
		}
		else
			c = c->next;
	}
}

void	merge_tokens(t_data *data)
{
	clear_out_es(data);
	join_tokens(data);
}
