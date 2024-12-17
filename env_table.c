/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:04:38 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/12/16 22:04:38 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_var	*getEnvVar(t_data *data, char *key)
{
	t_var	*curr;

	curr = NULL;
	if (!data->envVar)
		return NULL;
	curr = data->envVar;
	while (curr && strCmp(curr->key, key) != 0)
		curr = curr->next;
	if (!curr)
		return (NULL);
	return (curr);
}

void	setEnvVar(t_data *data, char *key, char *val)
{
	t_var	*new;

	new = getEnvVar(data, key);
	if (!new)
	{
		new = createEnvVar(key, val);
		new->next = data->envVar;
		data->envVar = new;
		return ;
	}
	free(new->val);
	new->val = strNDup(val, strLen(val));
}

void	unsetVar(t_data *data, char *key)
{
	t_var	*var;
	t_var	*next;
	t_var	*prev;

	var = NULL;
	next = NULL;
	prev = data->envVar;
	while (prev->next && strCmp(prev->next->key, key) != 0)
		prev = prev->next;
	if (!prev->next)
		return ;
	var = prev->next;
	next = var->next;
	prev->next = next;
	free(var->key);
	free(var->val);
	free(var);
}

t_var	*createEnvVar(char *key, char *val)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		exit(2);
	var->key = strNDup(key, strLen(key));
	var->val = strNDup(val, strLen(val));
	var->next = NULL;
	return (var);
}

void	copyEnv(t_data *data, char **envp)
{
    int		i;
	int		j;
	t_var	*new;
	t_var	*head;
	t_var	*tail;
	
	i = -1;
	head = NULL;
	tail = NULL;
	new = NULL;
    while (envp[++i] != 0)
    {
		j = -1;
		while (envp[i][++j] != '=');
		new = createEnvVar(strNDup(envp[i], j), envp[i] + j + 1);
		if (!head) 
		{
            head = new;
            tail = new;
			continue;
        }
        tail->next = new;
        tail = new;
    }
	data->envVar = head;
}
