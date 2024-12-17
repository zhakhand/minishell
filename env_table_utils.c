/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_table_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:44:29 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/12/17 10:54:32 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void setVar(t_env *env, char *key, char *val) 
{
	t_var	*new;

	new = getVal(env, key);
	if (new != NULL && strCmp(new->key, key) == 0)
	{
		free(new->val);
		new->val = strNDup(val, strLen(val));
		return ;
	}
	addVal(env, val, key);
}

void growTable(t_env *env)
{
	t_env	*new;

	new = initEnv(env->tableSize * 2);
	while (env->size-- > 0)
		addVal(new, env->vars[env->size]->val, env->vars[env->size]->key);
	free(env->vars);
	free(env);
	env = new;
}