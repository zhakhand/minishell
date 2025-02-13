/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:17:26 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 12:17:26 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_parent_buildin(t_cmd *node)
{
	if (node == NULL || node->cmd == NULL)
		return (-1);
	if (
		node->built_in == CD
		|| (node->built_in == EXPORT && node->args[1])
		|| node->built_in == UNSET
		|| node->built_in == EXIT)
	{
		return (0);
	}
	return (1);
}

int	check_child_buildin(t_cmd *node)
{
	if (node == NULL || node->cmd == NULL)
		return (-1);
	if (
		node->built_in == UNSET
		|| node->built_in == CD
		|| node->built_in == ECH
		|| node->built_in == PWD
		|| node->built_in == EXPORT
		|| node->built_in == ENV
		|| node->built_in == EXIT)
		return (0);
	return (1);
}

int	exec_buildin(t_data *data, t_cmd *node)
{
	int	res;

	res = 0;
	if (node == NULL || node->cmd == NULL)
		return (-1);
	if (node->built_in == CD && !node->prev)
		res = changedir(data, node);
	if (node->built_in == PWD)
		res = show_pwd(data);
	if (node->built_in == ECH)
		res = ft_echo(data, node);
	if (node->built_in == ENV)
		res = ft_env_no_args(data);
	if (node->built_in == UNSET)
		ft_unset(data, node);
	if (node->built_in == EXPORT)
		res = ft_export(data, node);
	if (node->built_in == EXIT)
		res = ft_exit(data, node);
	return (res);
}

void	s_e(t_data *data, int err_no)
{
	data->err_no = err_no;
}

int	is_valid_exit_code(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
