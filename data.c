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

t_data	*init_data(int ac, char **av, char **ev)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (!new)
		exit(2);
	new->env_var = NULL;
	new->argc = ac;
	new->err_no = 0;
	new->args = av;
	new->cmds = NULL;
	new->tokens = NULL;
	copy_env(new, ev);
	new->user = get_env_var(new, "USER");
	return (new);
}