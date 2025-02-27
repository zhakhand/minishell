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
#include "../minishell.h"

void	create_env(t_data *data)
{
	char	*pwd;
	t_var	*new;

	pwd = getcwd(NULL, 0);
	data->env_var = create_env_var(ft_strndup("PWD", 3, data), pwd, data);
	new = set_env_var(data, ft_strndup("OLDPWD", 6, data), "");
	new->is_valid = 0;
	if (pwd)
		free(pwd);
}

void	set_env(t_data *data, char **ev)
{
	if (!ev[0])
		create_env(data);
	else
		copy_env(data, ev);
}

t_data	*init_data(int ac, char **av, char **ev)
{
	t_data	*new;
	t_var	*temp;

	new = malloc(sizeof(t_data));
	if (!new)
		panic("malloc");
	ft_bzero(new, sizeof(t_data));
	new->out_fd = STDERR_FILENO;
	new->argc = ac;
	new->args = av;
	new->err_no = 0;
	new->we_have_child = 0;
	new->last_err = 0;
	new->redir_err = 0;
	set_env(new, ev);
	temp = get_env_var(new, "PATH");
	if (temp)
		new->path = ft_strndup(temp->val, str_len(temp->val), new);
	temp = get_env_var(new, "OLDPWD");
	if (temp)
		new->old_pwd = ft_strndup(temp->val, str_len(temp->val), new);
	temp = get_env_var(new, "PWD");
	if (temp)
		new->pwd = ft_strndup(temp->val, str_len(temp->val), new);
	return (new);
}
