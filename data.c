/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:00:42 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/12/16 21:00:42 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_data	*initData(int ac, char **av, char **ev)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (!new)
		exit(2);
	new->envVar = NULL;
	new->argc = ac;
	new->args = av;
	new->cmds = NULL;
	new->tokens = NULL;
	copyEnv(new, ev);
	new->user = getEnvVar(new, "USER");
	return (new);
}