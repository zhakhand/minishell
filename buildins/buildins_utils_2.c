/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:25:19 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 17:27:05 by oshcheho         ###   ########.fr       */
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
