/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:41:58 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/27 13:25:12 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include "../minishell.h"

t_cmd	*create_cmd_table(t_data *data)
{
	t_cmd	*cmd_table;

	cmd_table = malloc(sizeof(t_cmd));
	if (!cmd_table)
		end_it(data);
	ft_bzero(cmd_table, sizeof(t_cmd));
	cmd_table->args = NULL;
	cmd_table->in = -1;
	cmd_table->out = -1;
	return (cmd_table);
}

t_redir	*init_redir(t_data *data)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		end_it(data);
	new->type = 0;
	new->expands = 1;
	new->ambig = 0;
	new->val = NULL;
	new->heredoc = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_to_list(t_token *token, t_redir *tail)
{
	tail->type = token->prev->type;
	tail->val = token->val;
	if (token->prev->type == HEREDOC && token->was_quoted != 0)
		tail->expands = 0;
	if (token->is_ambiguous)
		tail->ambig = 1;
	token->val = NULL;
	if (token->prev->val)
		free(token->prev->val);
	token->prev->val = NULL;
}

t_redir	*redir_list(t_token *token, t_data *data)
{
	t_redir	*head;
	t_redir	*prev;
	t_redir	*tail;

	head = NULL;
	prev = NULL;
	while (token && token->type != PIPE)
	{
		if (is_redir(token->type) && token->next->type == WORD)
		{
			tail = init_redir(data);
			if (!head)
				head = tail;
			if (prev)
			{
				prev->next = tail;
				tail->prev = prev;
			}
			add_to_list(token->next, tail);
			prev = tail;
		}
		token = token->next;
	}
	return (head);
}

void	set_cmd_table(t_data *data)
{
	t_token	*token;
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*prev;

	head = create_cmd_table(data);
	current = head;
	prev = NULL;
	token = data->tokens;
	data->cmds = head;
	while (token)
	{
		if (current == NULL)
		{
			current = create_cmd_table(data);
			if (prev)
				prev->next = current;
		}
		token = put_cmds(token, current, data);
		prev = current;
		current = current->next;
	}
	check_built_in(data);
}
