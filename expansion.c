/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:52:52 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/12/19 16:19:51 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*link_tokens(t_token *token, t_token *head, t_token *curr, t_token *next)
{
	if (token->prev)
	{
		token->prev->next = head;
		head->prev = token->prev;
	}
	if (next)
	{
		next->prev = curr;
		curr->next = next;
	}
	free(token->val);
	free(token);
	return (head);
}

t_token	*set_quoted(t_token	*token, t_token	*head)
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
		curr = curr->next;
	}
	return (curr);
}

t_token	*break_down_tokens(t_token *token, t_token *next)
{
	t_token	*head;
	t_token	*curr;

	head = tokenize(token->val);
	curr = set_quoted(token, head);
	return link_tokens(token, head, curr, next);
}

void	clear_quote_tokens(t_data *data)
{
	t_token	*current;
	t_token	*next;
	// t_token	*head;

	current = data->tokens;
	next = NULL;
	while(current)
	{
		next = current->next;
		if (current->type == S_QUOTE || current->type == D_QUOTE )
		{
			if (!current->prev)
				data->tokens = break_down_tokens(current, next);
			else 
				current = break_down_tokens(current, next);
		}
		current = next;
	}
}

// t_token	*join_tokens(t_token *token, t_token *next, t_data *data)
// {
// 	t_var	*var;
// 	t_token	*head;
// 	t_token	*current;
// 	char	*merged;

// 	current = token;
// 	head = current;
// 	while (current)
// 	{
// 		current = current->next;
// 	}
// 	return NULL;
// }

// void	merge_tokens(t_data *data)
// {
// 	t_token *current;
// 	t_token	*next;

// 	current = data->tokens;
// 	next = NULL;
// 	while (current)
// 	{
// 		next = current->next;
// 		if ((current->type == WORD || current->type == VAR) && next)
// 		{
// 			if (next->type == WS)
// 			{
// 				current = next;
// 				continue ;
// 			}
// 			if (next->type == WORD || next->type == VAR)
// 			{
// 				current = join_tokens(current, next, data);
// 			}
// 		}
// 	}
// }

t_token	*check_expansion(t_token *token, t_token *next, t_data *data)
{
	t_var	*var;
	t_token	*head;
	t_token	*curr;

	head = NULL;
	curr = NULL;
	var = NULL;
	if (token->was_quoted != 1)
	{
		var = get_env_var(data, token->val + 1);
		if (!var)
		{
			token->ogVal = token->val;
			token->val = ft_strdup("");
			return token;
		}
		head = tokenize(var->val);
		set_quoted(token, head);
		return link_tokens(token, head, curr, next);
	}
	return (token);
}

void	expand_vars(t_data *data)
{
	t_token	*current;
	t_token	*next;

	current = data->tokens;
	next = NULL;
	while (current)
	{
		next = current->next;
		if (current->type == VAR)
		{
			if (!current->prev)
				data->tokens = check_expansion(current, next, data);
			else
				current = check_expansion(current, next, data);
		}
		current = next;
	}
}

void	reorder_tokens(t_data *data)
{
	clear_quote_tokens(data);
	expand_vars(data);
	//merge_tokens(data);
}
