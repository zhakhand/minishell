/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:03:16 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/12/16 17:34:58 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

// void	print_cmd_table(t_cmd *cmd)
// {
// 	t_cmd	*curr;
// 	t_redir	*red;
// 	int		i;
// 	int		j;

// 	j = 0;
// 	curr = cmd;
// 	printf("*******Command Table*********\n");
// 	while (curr)
// 	{
// 		i = 0;
// 		printf("***%d***\n", j);
// 		if (curr->cmd)
// 			printf("CMD: %s\n", curr->cmd);
// 		if (curr->args)
// 		{
// 			printf("ARGS: ");
// 			while (curr->args[i])
// 				printf("[%s] ", curr->args[i++]);
// 			printf("\n");
// 		}
// 		if (curr->redir)
// 		{
// 			red = curr->redir;
// 			printf("REDIRS: ");
// 			while (red)
// 			{
// 				printf("[%s, %d]", red->val, red->type);
// 				red = red->next;
// 			}
// 			printf("\n");
// 		}
// 		printf("BUILT IN: %d\n", curr->built_in);
// 		printf("IN File: %d\n", curr->in);
// 		printf("OUT File: %d\n", curr->out);
// 		j++;
// 		curr = curr->next;
// 	}
// }

void	find_error(t_data *data)
{
	t_token	*curr;

	curr = data->tokens;
	while (curr)
	{
		if (curr->type == ERROR && curr->was_quoted != 1)
		{
			curr->ogVal = curr->val;
			curr->val = ft_itoa(data->err_no);
			curr->type = WORD;
		}
		curr = curr->next;
	}
}

void	mark_merges(t_token *tokens)
{
	t_token	*curr;

	curr = NULL;
	if (tokens)
		curr = tokens;
	while (curr)
	{
		if ((curr->type == WORD || curr->type == D_QUOTE \
		|| curr->type == S_QUOTE || curr->type == VAR || curr->type == ERROR) \
		&& curr->next && (curr->next->type == WORD \
		|| curr->next->type == D_QUOTE || curr->next->type == S_QUOTE \
		|| curr->next->type == VAR || curr->next->type == ERROR))
		{
			curr->touches_next = 1;
		}
		curr = curr->next;
	}
}

void	mark_vars(t_data *data)
{
	t_token	*curr;

	curr = NULL;
	if (data->tokens)
		curr = data->tokens;
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			curr = curr->next;
			while (curr)
			{
				curr->type = WORD;
				curr->is_delim = 1;
				if (curr->touches_next)
					curr = curr->next;
				else
					break ;
			}
		}
		curr = curr->next;
	}
}

int	reorder_tokens(t_data *data)
{
	mark_merges(data->tokens);
	delete_spaces(data);
	if (check_redirs(data))
		return (ERROR);
	if (check_pipes(data))
		return (ERROR);
	mark_vars(data);
	clear_quote_tokens(data);
	find_error(data);
	expand_vars(data);
	delete_spaces(data);
	merge_tokens(data);
	return (0);
}
