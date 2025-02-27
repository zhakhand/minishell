/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:15:44 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/27 13:54:31 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_redir(int type)
{
	return (type == IN || type == OUT || type == HEREDOC || type == APPEND);
}

t_token	*count_args(int *count, t_token *token)
{
	t_token	*tail;

	tail = token;
	while (tail && tail->type != PIPE)
	{
		if (tail->val != NULL)
			(*count)++;
		tail = tail->next;
	}
	return (tail);
}

void	fill_args(t_cmd *cmd, t_token *token)
{
	int		i;
	t_token	*curr;

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

t_token	*put_cmds(t_token *token, t_cmd *cmd, t_data *data)
{
	int		count;
	t_token	*tail;

	count = 0;
	cmd->redir = redir_list(token, data);
	tail = count_args(&count, token);
	cmd->args = ft_calloc(count, sizeof(char *));
	if (!cmd->args)
		end_it(data);
	fill_args(cmd, token);
	cmd->args_count = count;
	cmd->cmd = cmd->args[0];
	if (tail)
		return (tail->next);
	return (NULL);
}
