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

#include "../parser.h"

t_data	*init_data(int ac, char **av, char **ev)
{
	t_data	*new;
	t_var	*temp;

	new = malloc(sizeof(t_data));
	if (!new)
		exit(2);
	ft_bzero(new, sizeof(t_data));
	new->argc = ac;
	new->args = av;
	new->err_no = 0;
	new->last_err = 0;
	new->redir_err = 0;
	copy_env(new, ev);
	temp = get_env_var(new, "PATH");
	if (temp)
		new->path = ft_strdup(temp->val);
	temp = get_env_var(new, "OLDPWD");
	if (temp)
		new->old_pwd = ft_strdup(temp->val);
	temp = get_env_var(new, "PWD");
	if (temp)
		new->pwd = ft_strdup(temp->val);
	new->user = get_env_var(new, "USER");
	return (new);
}
