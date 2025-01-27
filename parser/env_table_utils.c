/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_table_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:28:54 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/27 13:04:41 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

t_var	*push_back(t_data *data, t_var *new)
{
	t_var	*temp;

	temp = NULL;
	if (data->env_var)
		temp = data->env_var;
	while (temp)
	{
		if (!temp->next)
			break ;
		temp = temp->next;
	}
	temp->next = new;
	return (new);
}

void	unset_var(t_data *data, char *key)
{
	t_var	*var;
	t_var	*next;
	t_var	*prev;

	var = NULL;
	next = NULL;
	prev = data->env_var;
	while (prev->next && ft_strcmp(prev->next->key, key) != 0)
		prev = prev->next;
	if (!prev->next)
		return ;
	var = prev->next;
	next = var->next;
	prev->next = next;
	free(var->key);
	var->key = NULL;
	free(var->val);
	var->val = NULL;
	free(var);
	var = NULL;
}
