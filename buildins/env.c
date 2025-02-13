/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:18:10 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 12:18:10 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env_no_args(t_data *data)
{
	t_var	*temp;

	if (!data->env_var)
		return (EXIT_FAILURE);
	temp = data->env_var;
	while (temp)
	{
		if (temp->is_valid == 1)
		{
			if (temp->key)
			{
				ft_putstr_fd(temp->key, STDOUT_FILENO);
				ft_putstr_fd("=", STDOUT_FILENO);
			}
			if (temp->val)
			{
				ft_putstr_fd(temp->val, STDOUT_FILENO);
			}
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
