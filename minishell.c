/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:41:26 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/13 18:58:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int main(int ac, char **av, char **ev)
{
	char *line;
	t_data *data;
	int err_no;
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


//	print_cmd_table(data->cmds);
	data->path_arr = get_path_arr(ev);
	err_no = execute(data, ev);
	
	clean_data(data);
	return (err_no);

}