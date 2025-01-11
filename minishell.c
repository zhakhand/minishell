/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:41:26 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/11 17:31:25 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

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
	data->path_arr = get_path_arr(ev);
	execute(data, ev);
	clean_data(data);

}