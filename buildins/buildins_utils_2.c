/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:25:19 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/27 14:01:38 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_no_args(t_data *data, t_cmd *node)
{
	long	exit_code;

	exit_code = data->err_no;
	if (node->next != NULL || data->we_have_child == 1)
		return (data->err_no);
	ft_putstr_fd("exit\n", 1);
	clean_data(data);
	exit (exit_code);
}

void	clean_exit(t_data *data, int exit_code)
{
	ft_putstr_fd("exit\n", 1);
	clean_data(data);
	exit (exit_code);
}

char	*get_i_for_cd_up(t_data *data)
{
	int		i;
	char	*pwd;

	i = ft_strlen(data->pwd);
	while (i > 0)
	{
		if (data->pwd[i] == '/')
			break ;
		i--;
	}
	if (i == 0)
		pwd = ft_strdup("/");
	else
		pwd = ft_substr(data->pwd, 0, i);
	if (!pwd)
		end_it(data);
	return (pwd);
}
