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

#include "../parser.h"

t_var	*get_env_var(t_data *data, char *key)
{
	t_var	*curr;

	curr = NULL;
	if (!data->env_var)
		return NULL;
	curr = data->env_var;
	while (curr && ft_strcmp(curr->key, key) != 0)
		curr = curr->next;
	if (!curr)
		return (NULL);
	return (curr);
}

t_var	*set_env_var(t_data *data, char *key, char *val)
{
	t_var	*new;

	new = get_env_var(data, key);
	if (!new)
	{
		new = create_env_var(key, val);
		new->next = data->env_var;
		data->env_var = new;
		return (new);
	}
	free(new->val);
	new->val = ft_strndup(val, str_len(val));
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
	free(var->val);
	free(var);
}

t_var	*create_env_var(char *key, char *val)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		exit(2);
	var->key = ft_strndup(key, str_len(key));
	if (key)
		free(key);
	key = NULL;
	var->is_valid = 1;
	var->val = ft_strndup(val, str_len(val));
	var->next = NULL;
	return (var);
}

void	copy_env(t_data *data, char **envp)
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
		new = create_env_var(ft_strndup(envp[i], j), envp[i] + j + 1);
		if (!head) 
		{
            head = new;
            tail = new;
			continue;
        }
        tail->next = new;
        tail = new;
    }
	data->env_var = head;
}
