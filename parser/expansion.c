/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:52:52 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/09 19:47:59 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

t_token *link_tokens(t_token *token, t_token *head, t_token *tail)
{
	if (token->prev)
	{
		token->prev->next = head;
		head->prev = token->prev;
	}
	if (token->next)
	{
		token->next->prev = tail;
		tail->next = token->next;
	}
	free(token->val);
	free(token);
	return (head);
}

t_token *set_quoted(t_token *token, t_token *head)
{
	t_token *curr;

	curr = head;
	while (curr)
	{
		if (token->type == S_QUOTE)
			curr->was_quoted = 1;
		else
			curr->was_quoted = 2;
		if (!curr->next)
			break;
		curr = curr->next;
	}
	return (curr);
}

t_token *break_down_tokens(t_token *token)
{
	t_token *head;
	t_token *curr;

	head = tokenize_quotes_vars(token->val);
	curr = set_quoted(token, head);
	return link_tokens(token, head, curr);
}

void clear_quote_tokens(t_data *data)
{
	t_token *current;
	t_token *next;

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

int	is_delim(t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr && (curr->type == WORD || curr->type == VAR || \
	curr->type == D_QUOTE || curr->type == S_QUOTE || curr->was_quoted))
		curr = curr->prev;
	if (curr && curr->prev->type == HEREDOC)
		return (1);
	else if (curr && curr->type == HEREDOC)
		return (1);
	return (0);
}

t_token *check_expansion(t_token *token, t_data *data)
{
	t_var *var;
	t_token *head;
	t_token *curr;

	head = NULL;
	curr = NULL;
	if (is_delim(token))
	{
		token->type = WORD;
		return (token);
	}
	if (token->was_quoted != 1)
	{
		var = get_env_var(data, token->val + 1);
		if (!var)
		{
			token->ogVal = token->val;
			token->val = ft_strdup("");
			token->type = WORD;
			return token;
		}
		if (token->was_quoted == 2)
		{
			token->val = NULL;
			token->val = ft_strdup(var->val);
			token->type = WORD;
			return (token);
		}
		head = tokenize_quotes_vars(var->val);
		curr = head;
		while (curr->next)
			curr = curr->next;
		// curr = set_quoted(token, head);
		return link_tokens(token, head, curr);
	}
	token->type = WORD;
	return (token);
}

void expand_vars(t_data *data)
{
	t_token *current;
	t_token *next;

	current = data->tokens;
	next = NULL;
	while (current)
	{
		next = current->next;
		if (current->type == VAR)
		{
			if (!current->prev)
				data->tokens = check_expansion(current, data);
			else
				current = check_expansion(current, data);
		}
		current = next;
	}
}

void	find_error(t_data *data)
{
	t_token *curr;
	
	curr = data->tokens;
	while (curr)
	{
		if (curr->type == ERROR)
		{
			curr->ogVal = curr->val;
			curr->val = ft_itoa(data->err_no);
			curr->type = WORD;
		}
		curr = curr->next;
	}
}

void reorder_tokens(t_data *data)
{
	find_error(data);
	merge_tokens(data);
	clear_quote_tokens(data);
	expand_vars(data);
	merge_tokens(data);
	delete_spaces(data);
	check_pipes(data);
	check_redirs(data);
	syntax_check(data);
}
