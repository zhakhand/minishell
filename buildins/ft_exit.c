/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:33:14 by marvin            #+#    #+#             */
/*   Updated: 2025/01/13 16:33:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_exit(t_data *data, t_cmd *node)
{
	int i;
	int exit_code;

	i = 0;
	exit_code = 0;
	if (node->args[1] == NULL)
	{
		clean_data(data);
		exit(0);
	}
	else if (node->args[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	else
	{
		while (node->args[1][i])
		{
			if (ft_isdigit(node->args[1][i]) == 0 && node->args[1][i] != '+' && node->args[1][i] != '-')
			{
				ft_putstr_fd(" minishell: exit: \n", STDERR_FILENO);
//				ft_putstr_fd(node->args[1], STDERR_FILENO);
				ft_putstr_fd(" numeric argument required\n", STDERR_FILENO);
				return (2);
			}
			i++;
		}

		exit_code = ft_atoi(node->args[1]);
//		printf("exit  %d \n", exit_code);
		clean_data(data);
		exit(exit_code);
	}
	return (exit_code);
}