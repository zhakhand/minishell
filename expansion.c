/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:52:52 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/12/17 18:52:35 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	merge_tokens(t_token *prev, t_token *curr)
{
	
}

void	increment_indices(t_token *token)
{
	t_token	*first;
	t_token *curr;
	t_token	*last;

	curr = token;
	first = token;
	last = NULL;
	while (curr)
	{
		while (curr->next && curr->index == curr->next->index)
			curr = curr->next;
		last = curr;
		while (first != last)
		{
			first->index = token->prev->index + 1;
			first->next;
		}
		last->index = token->prev->index + 1;
		first = last->next;
		curr = last->next;
	}
}

void	delete_spaces(t_token *token)
{
	int	i;
	int	len;

	i = 0;
	len = str_len(token->val);
	if (token->val[0] == 32 && token->prev && token->index == token->prev->index)
		token->index = token->prev->index + 1;
	if (token->val[len - 1] == 32 && token->next && token->index <= token->next->index)
		increment_indices(token->next);
	
}

void	check_spaces(t_data *data)
{
	t_token	*curr;
	
	curr = data->env_var;
	while (curr && (curr->type == D_QUOTE || curr->type == S_QUOTE))
	{
		if (ft_strchr(curr->val, 32) != NULL)
			delete_spaces(curr);
		curr = curr->next;
	}
}

void	reorder_tokens(t_data *data)
{
	check_spaces(data);
}