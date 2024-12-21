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

void	set_cmd_table(t_data *data)
{
	t_token	*current;
	t_cmd	*cmd_table;

	char	**args;
}