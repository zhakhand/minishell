/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:18:48 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 12:18:48 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	show_pwd(t_data *data)
{
	if (data->pwd != NULL)
	{
		ft_putstr_fd(data->pwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	else
		ft_putstr_fd("PWD not set\n", STDERR_FILENO);
	return (1);
}

int	get_i_for_cd_up(t_data *data)
{
	int	i;

	i = ft_strlen(data->pwd);
	while (i > 0)
	{
		if (data->pwd[i] == '/')
			break ;
		i--;
	}
	return (i);
}
