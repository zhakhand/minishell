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

int	hash(char *key, t_env *env)
{
	int		i;
	int		hash;

	i = 0;
	hash = 0;
	while (key[i] != '\0')
	{
		hash += key[i];
		i++;
	}
	return ((hash % env->tableSize) + env->n) % env->tableSize;
}

t_var *getVal(t_env *env, char *key)
{
    int index;
    size_t i;
	size_t k;

	i = 0;
	k = env->n;
    if (env->size == 0)
        return NULL;
    index = hash(key, env);
    while (i < k && env->vars[index] != NULL && strCmp(env->vars[index]->key, key) != 0) {
        env->n = i;
        i++;
        index = hash(key, env);
        if (i >= k) {
            env->n = k;
            return NULL;
        }
    }
	env->n = k;
    if (env->vars[index] != NULL && strCmp(env->vars[index]->key, key) == 0)
        return env->vars[index];
    return NULL;
}


void	addVal(t_env *env, char *val, char *key)
{
	int		index;
	t_var *new;

	if (env->size == env->tableSize)
	{
		growTable(env);
	}
	if (getVal(env, key) != NULL)
		return ;
	new = malloc(sizeof(t_var));
	if (!new)
		exit(2);
	new->key = strNDup(key, strLen(key));
	new->val = strNDup(val, strLen(val));
	index = hash(key, env);
	while (env->vars[index] != NULL)
	{
		env->n++;
		index = hash(key, env);
	}
	env->vars[index] = new;
	env->size++;
}

t_env	*initEnv(int size)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		exit(2);
	new->vars = (t_var **)malloc(sizeof(t_var *) * (size + 1));
	if (!new->vars)
		exit(2);
	new->vars[size] = NULL;
	new->tableSize = size;
	while (size-- > 0)
		new->vars[size] = NULL;
	new->size = 0;
	new->n = 0;
	return (new);
}

void	copyEnv(t_data *data, char **envp)
{
    int		i;
	int		j;
	char	*val;
	char	*key;
	
	i = 0;
	j = 0;
	while (envp[i] != 0)
		i++;
	data->env = initEnv(i);
	i = 0;
    while (envp[i] != 0)
    {
		j = 0;
		while (envp[i][j] != '=')
			j++;
		key = strNDup(envp[i], j);
		val = strNDup(envp[i] + j + 1, strLen(envp[i]) + j);
		addVal(data->env, val, key);
		free(key);
		free(val);
		i++;
    }
}
