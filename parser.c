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

	data = initData();
	data->argc = ac;
	data->args = av;
	copyEnv(data, ev);
	t_var *userInfo = getVal(data->env, "PWD");
	printf("%s=%s\n", userInfo->key, userInfo->val);
	while (1)
	{
		line = readline("> ");
		tokens = tokenize(line);
		free(line);
		break;
	}
	int i = 0;
	while (data->env->vars[i] != NULL){
		printf("[%s] \n", data->env->vars[i]->val);
		i++;
	}
	while (tokens){
		printf("[%s, %d] ", tokens->val, tokens->index);
		tokens = tokens->next;
	}
    printf("\n");
}