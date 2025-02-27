/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:18:29 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 12:18:29 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_no_args(t_data *data)
{
	int		i;
	char	**tmp;

	tmp = make_env_arr(data);
	tmp = sort_env(tmp);
	i = 0;
	while (tmp[i] != NULL)
	{
		if (tmp[i][0] != '_')
		{
			data->out_fd = 1;
			ft_putmsg_fd("declare -x ", tmp[i], "\n", data);
		}
		i++;
	}
	free_args(&tmp);
	tmp = NULL;
}

int	ft_export(t_data *data, t_cmd *node)
{
	int	i;

	if (node->next != NULL)
		return (0);
	if (node->args[1] == NULL)
		return (export_no_args(data), 0);
	i = 1;
	if (check_symbols(node->args[1]) == 1)
		return (ft_putmsg_fd("export: `", node->args[1], NVI, data), 1);
	while (node->args[i] != NULL)
	{
		add_to_env_end(node->args[i], data);
		i++;
	}
	return (0);
}
