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
	t_token	*tokens;
	//t_cmd	*cmd;

	data = initData(ac, av, ev);
	while (1)
	{
		line = readline("> ");
		tokens = tokenize(line);
		free(line);
		break;
	}
	while (data->envVar != NULL){
		printf("[%s] \n", data->envVar->val);
		data->envVar = data->envVar->next;
	}
	while (tokens){
		printf("[%s, %d] ", tokens->val, tokens->index);
		tokens = tokens->next;
	}
    printf("\n");
}