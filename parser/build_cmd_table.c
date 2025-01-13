/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:41:58 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/11 12:09:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

t_cmd *create_cmd_table()
{
	t_cmd *cmd_table;

	cmd_table = malloc(sizeof(t_cmd));
	if (!cmd_table)
		exit(2);
	ft_bzero(cmd_table, sizeof(t_cmd));
	cmd_table->in = -1;
	cmd_table->out = -1;
	return cmd_table;
}

int	is_redir(int type)
{
	return (type == IN || type == OUT || type == HEREDOC || type == APPEND);
}

t_token *count_args(int *count, t_token *token)
{
	t_token *tail;

	tail = token;
	while (tail && tail->type != PIPE)
	{
		if (tail->val != NULL)
			(*count)++;
		tail = tail->next;
	}
	return (tail);
}

void fill_args(t_cmd *cmd, t_token *token)
{
	int i;
	t_token *curr;

	i = 0;
	curr = token;
	while (curr && curr->type != PIPE)
	{
		if (curr->val != NULL)
		{
			cmd->args[i] = curr->val;
			curr->val = NULL;
			i++;
		}
		curr = curr->next;
	}
}

t_redir	*init_redir()
{
	t_redir *new;
	
	new = malloc(sizeof(t_redir));
	if (!new)
		exit(2);
	new->type = 0;
	new->val = NULL;
	new->next = NULL;
	new->prev = NULL;
	return new;
}


t_redir	*redir_list(t_token *token)
{
	t_redir	*head;
	t_redir *prev;
	t_redir	*tail;
//	t_token	*curr;

//	curr = token;
	head = NULL;
	prev = NULL;
	while (token && token->type != PIPE)
	{
		if (token->prev && is_redir(token->prev->type))
		{
			tail = init_redir();
			if (!head)
				head = tail;
			if (prev)
			{
				prev->next = tail;
				tail->prev = prev;
			}
			tail->type = token->prev->type;
			tail->val = token->val;
			if (token->prev->type == HEREDOC && token->was_quoted == 2 && token->ogVal)
				tail->val = token->ogVal;
			token->val = NULL;
			free(token->prev->val);
			token->prev->val = NULL;
			prev = tail;
		}
		token = token->next;
	}
	return head;
}

t_token *put_cmds(t_token *token, t_cmd *cmd)
{
	int count;
	t_token *tail;

	count = 0;
	cmd->redir = redir_list(token);
	tail = count_args(&count, token);
	cmd->args = ft_calloc(count, sizeof(char *));
	fill_args(cmd, token);
	cmd->cmd = cmd->args[0];
	if (tail)
		return tail->next;
	return (NULL);
}

void set_cmd_table(t_data *data)
{
	t_token *token;
	t_cmd 	*head;
	t_cmd 	*current;
	t_cmd	*prev;

	head = create_cmd_table();
	current = head;
	prev = NULL;
	token = data->tokens;
	data->cmds = head;
	while (token)
	{
		if (current == NULL)
		{
			current = create_cmd_table();
			if (prev)
				prev->next = current;
		}
		token = put_cmds(token, current);
		prev = current;
		current = current->next;
	}
	check_built_in(data);
}
