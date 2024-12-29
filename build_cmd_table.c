/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:41:58 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/12/21 14:41:58 by dzhakhan         ###   ########.fr       */
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
	cmd_table->redirs = NULL;
	cmd_table->args = NULL;
	cmd_table->cmd = NULL;
}

t_token *count_args(int *count, int *r_count, t_token *token)
{
	t_token *tail;

	tail = token;
	while (tail && tail->type != PIPE)
	{
		if (tail->type == IN || tail->type == OUT || tail->type == HEREDOC || tail->type || APPEND)
		{
			r_count++;
			count++;
		}
		else
			count++;
		tail = tail->next;
	}
	return (tail);
}

void create_arrays(t_cmd *cmd, int count, int r_count)
{
	cmd->args = (char **)malloc(sizeof(char *) * count + 1);
	if (!cmd->args)
		exit(1);
	cmd->redirs = (char **)malloc(sizeof(char *) * r_count + 1);
	if (!cmd->redirs)
		exit(1);
	cmd->args[count] = 0;
	cmd->redirs[r_count] = 0;
}

void fill_args(t_cmd *cmd, int count, int r_count, t_token *token)
{
	int i;
	t_token *curr;

	i = 0;
	curr = token;
	while (i < count)
	{
		cmd->cmd[i] = curr->val;
		curr = curr->next;
		i++;
	}
	i = 0;
	while (i < r_count) // IS << >> < > arg?
	{
		cmd->redirs
	}
}

t_token *put_cmds(t_token *token, t_cmd *cmd)
{
	int count;
	int r_count;
	t_token *tail;

	count = 0;
	r_count = 0;
	tail = count_args(&count, &r_count, token);
	create_arrays(cmd, count, r_count);
	cmd->cmd = token->val;
	fill_args(cmd, count, r_count, token);
}

void set_cmd_table(t_data *data)
{
	t_token *token;
	t_cmd *head;
	t_cmd *current;

	head = create_cmd_table();
	curr = head;
	token = data->tokens;
	data->cmds = head;
	while (token)
	{
		token = put_cmds(token, current);
		current = current->next;
	}
}