/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:41:26 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/15 10:54:26 by marvin           ###   ########.fr       */
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

//printf("1\n");
	data = init_data(ac, av, ev);
	data->err_no = 0;
	while (1)
	{
		line = readline("> ");
		if (ft_strlen(line) == 0)
			continue ;
		data->tokens = tokenize(line);
		data->path_arr = get_path_arr(ev);
		reorder_tokens(data);
		set_cmd_table(data);
		data->err_no = run_pipe(data, data->cmds, ev);
		// free_tokens(data->tokens);
		// free_cmds(data->cmds);
		// add_history(line);
		free(line);
		break;
	}


//	print_cmd_table(data->cmds);
	err_no = data->err_no;
	clean_data(data);
	return (err_no);

}