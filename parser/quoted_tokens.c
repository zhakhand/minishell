/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:17:39 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/27 12:54:38 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

t_token	*link_tokens(t_token *token, t_token *head, t_token *tail)
{
	if (token->prev)
	{
		token->prev->next = head;
		if (head)
			head->prev = token->prev;
	}
	if (token->next)
	{
		token->next->prev = tail;
		tail->next = token->next;
	}
	if (token->val)
		free(token->val);
	token->val = NULL;
	if (token->ogVal)
		free(token->ogVal);
	token->ogVal = NULL;
	if (token)
		free(token);
	token = NULL;
	return (head);
}

t_token	*set_quoted(t_token *token, t_token *head)
{
	t_token	*curr;

	curr = head;
	while (curr)
	{
		if (token->type == S_QUOTE)
			curr->was_quoted = 1;
		else
			curr->was_quoted = 2;
		if (!curr->next)
			break ;
		curr->touches_next = 1;
		curr = curr->next;
	}
	if (token->touches_next == 1)
		curr->touches_next = 1;
	return (curr);
}

t_token	*break_down_tokens(t_token *token)
{
	t_token	*head;
	t_token	*curr;

	head = NULL;
	curr = NULL;
	head = tokenize_quotes_vars(token->val);
	curr = set_quoted(token, head);
	return (link_tokens(token, head, curr));
}

void	clear_quote_tokens(t_data *data)
{
	t_token	*current;
	t_token	*next;

	current = data->tokens;
	next = NULL;
	while (current)
	{
		next = current->next;
		if (current->type == S_QUOTE || current->type == D_QUOTE)
		{
			if (!current->prev)
				data->tokens = break_down_tokens(current);
			else
				current = break_down_tokens(current);
		}
		current = next;
	}
}
