/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:41:58 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/04 15:54:51 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd *create_cmd_table()
{
	t_cmd *cmd_table;

	cmd_table = malloc(sizeof(t_cmd));
	if (!cmd_table)
		exit(2);
	cmd_table->next = NULL;
	cmd_table->prev = NULL;
	cmd_table->redir = NULL;
	cmd_table->args = NULL;
	cmd_table->cmd = NULL;
	return cmd_table;
}

int	is_redir(int type)
{
	return (type == IN || type == OUT || type == HEREDOC || type == APPEND);
}

/*****
 * << >> < > should be in different cmd tables? NO
 * put redirs also in args[]? NO
 * 
******/

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

void create_arrays(t_cmd *cmd, int count)
{
	cmd->args = (char **)malloc((sizeof(char *) * count) + 1);
	if (!cmd->args)
		exit(1);
}

void fill_args(t_cmd *cmd, int count, t_token *token)
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
	cmd->args[i] = 0;
	i = -1;
	while (++i < count)
		printf("%s\n", cmd->args[i]);
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
	t_token	*curr;
	t_redir	*head;
	t_redir *prev;
	t_redir	*tail;

	curr = token;
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
	create_arrays(cmd, count);
	fill_args(cmd, count, token);
	cmd->cmd = cmd->args[0];
	if (tail)
		return tail->next;
	return (NULL);
}

void set_cmd_table(t_data *data)
{
	t_token *token;
	t_cmd *head;
	t_cmd *current;

	head = create_cmd_table();
	current = head;
	token = data->tokens;
	data->cmds = head;
	while (token)
	{
		if (current == NULL)
			current = create_cmd_table();
		token = put_cmds(token, current);
		t_redir	*red = current->redir;
		while (red){
			printf("{%s}", red->val);
			red = red->next;
		}
		current = current->next;
	}
}