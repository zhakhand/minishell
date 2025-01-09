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

#include "parser.h"

void	print_cmd_table(t_cmd *cmd)
{
	t_cmd	*curr;
	t_redir	*red;
	int		i;
	int		j;

	j = 0;
	curr = cmd;
	printf("*******Command Table*********\n");
	while (curr)
	{
		i = 0;
		printf("***%d***\n", j);
		if (curr->cmd)
			printf("CMD: %s\n", curr->cmd);
		if (curr->args)
		{
			printf("ARGS: ");
			while (curr->args[i])
				printf("[%s] ", curr->args[i++]);
			printf("\n");
		}
		if (curr->redir)
		{
			red = curr->redir;
			printf("REDIRS: ");
			while (red)
			{
				printf("[%s, %d]", red->val, red->type);
				red = red->next;
			}
			printf("\n");
		}
		printf("BUILT IN: %d\n", curr->built_in);
		printf("IN File: %d\n", curr->in);
		printf("OUT File: %d\n", curr->out);
		j++;
		curr = curr->next;
	}
}

int main(int ac, char **av, char **ev)
{
	char *line;
	t_data *data;
	// t_cmd	*cmd;

	data = init_data(ac, av, ev);
	while (1)
	{
		line = readline("> ");
		data->tokens = tokenize(line);
		reorder_tokens(data);
		set_cmd_table(data);
		free(line);
		break;
	}
	print_cmd_table(data->cmds);
	clean_data(data);
}
