/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:34:45 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/27 12:36:42 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

t_token	*handle_nonex_invalid(t_token *token, t_var *var, t_data *data)
{
	if (!var && token->prev && is_redir(token->prev->type) \
	&& !token->touches_next)
	{
		token->is_ambiguous = 1;
		token->type = WORD;
		return (token);
	}
	if (token->val)
		free(token->val);
	token->val = NULL;
	token->val = ft_strdup("");
	if (!token->val)
		end_it(data);
	token->type = ES;
	return (token);
}

t_token	*handle_quoted_var(t_token *token, t_var *var, t_data *data)
{
	if (token->val)
		free(token->val);
	token->val = NULL;
	token->val = ft_strdup(var->val);
	if (!token->val)
		end_it(data);
	token->type = WORD;
	return (token);
}

t_token	*handle_normal_var(t_token *token, t_var *var, t_data *data)
{
	t_token	*head;
	t_token	*curr;

	head = NULL;
	curr = NULL;
	if (data->line)
		free(data->line);
	data->line = NULL;
	head = tokenize_quotes_vars(var->val, data);
	curr = head;
	while (curr && curr->next)
		curr = curr->next;
	if (token->prev && token->prev->touches_next == 1 && head->type == WS)
		token->prev->touches_next = 0;
	mark_merges(head);
	if (token->touches_next && curr->type != WS)
		curr->touches_next = 1;
	return (link_tokens(token, head, curr));
}

t_token	*check_expansion(t_token *token, t_data *data)
{
	t_var	*var;

	var = NULL;
	if (token->was_quoted != 1)
	{
		var = get_env_var(data, token->val + 1);
		if (!var || (var && var->is_valid == 0) \
		|| (var && var->is_valid == 1 && !ft_strlen(var->val)))
			return (handle_nonex_invalid(token, var, data));
		if (token->was_quoted == 2)
			return (handle_quoted_var(token, var, data));
		return (handle_normal_var(token, var, data));
	}
	token->type = WORD;
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
				data->tokens = check_expansion(current, data);
			else
				current = check_expansion(current, data);
		}
		current = next;
	}
}
