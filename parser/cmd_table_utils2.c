/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:21:54 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/03/04 17:23:22 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	add_to_list_no_del(t_token *token, t_redir *tail, t_data *data)
{
	tail->type = token->prev->type;
	tail->val = ft_strdup(token->val);
	if (!tail->val)
		end_it(data);
	if (token->prev->type == HEREDOC && token->was_quoted != 0)
		tail->expands = 0;
	if (token->is_ambiguous)
		tail->ambig = 1;
}

t_redir	*redir_list_out(t_token *token, t_data *data)
{
	t_redir	*head;
	t_redir	*prev;
	t_redir	*tail;

	head = NULL;
	prev = NULL;
	while (token && token->type != PIPE)
	{
		if (is_redir(token->type) && token->next->type == WORD \
		&& (token->type == OUT || token->type == APPEND))
		{
			tail = init_redir(data);
			if (!head)
				head = tail;
			if (prev)
			{
				prev->next = tail;
				tail->prev = prev;
			}
			add_to_list_no_del(token->next, tail, data);
			prev = tail;
		}
		token = token->next;
	}
	return (head);
}
