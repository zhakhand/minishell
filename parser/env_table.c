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
#include "../minishell.h"

t_var	*get_env_var(t_data *data, char *key)
{
	t_var	*curr;

	curr = NULL;
	if (!data->env_var)
		return (NULL);
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
		new = create_env_var(key, val, data);
		return (push_back(data, new));
	}
	if (key && *key)
		free(key);
	key = NULL;
	free(new->val);
	new->val = NULL;
	new->val = ft_strndup(val, str_len(val), data);
	return (new);
}

t_var	*create_env_var(char *key, char *val, t_data *data)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		end_it(data);
	var->key = ft_strndup(key, str_len(key), data);
	if (key)
		free(key);
	key = NULL;
	var->is_valid = 1;
	var->val = ft_strndup(val, str_len(val), data);
	var->next = NULL;
	return (var);
}

int	move_index(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '=')
		;
	return (i);
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
		j = move_index(envp[i]);
		new = create_env_var(ft_strndup(envp[i], j, data), \
		envp[i] + j + 1, data);
		if (!head)
		{
			head = new;
			tail = new;
			continue ;
		}
		tail->next = new;
		tail = new;
	}
	data->env_var = head;
}
