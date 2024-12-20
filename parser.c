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


int	main(int ac, char **av, char **ev)
{
	char	*line;
	t_data	*data;
	//t_cmd	*cmd;

	data = init_data(ac, av, ev);
	while (1)
	{
		line = readline("> ");
		data->tokens = tokenize(line);
		reorder_tokens(data);
		free(line);
		break;
	}
	// while (data->env_var != NULL){
	// 	printf("[%s] \n", data->env_var->val);
	// 	data->env_var = data->env_var->next;
	// }
	while (data->tokens && data->tokens->val){
		printf("[%s] ", data->tokens->val);
		data->tokens = data->tokens->next;
	}
}