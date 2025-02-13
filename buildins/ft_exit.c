/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:18:34 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 12:18:34 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_signs(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (str[0] == '\0')
		return (1);
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ')
			res = 1;
		if (str[i] == ' ' && ft_isdigit(str[i + 1]))
			res = 1;
		i++;
	}
	return (res);
}

int	handle_beginning(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

long	ft_atol(char *str)
{
	int		i;
	long	res;
	int		sign;

	i = handle_beginning(str);
	res = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		if (res == 922337203685477580 && (str[i] - '0') == 8 && sign == -1)
			return (0);
		if (res > (LONG_MAX / 10)
			|| (res == (LONG_MAX / 10) && (str[i] - '0' > (LONG_MAX % 10))))
			return (-1);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

long	ft_exit_atol(t_data *data, t_cmd *n)
{
	long	exit_code;

	if (n->args[2] != NULL)
		return (s_e(data, 1), ft_putstr_fd(E_T_M_A, STDERR_FILENO), 1);
	else
	{
		if (ft_strcmp(n->args[1], "-1") == 0)
			exit_code = 255;
		else
		{
			exit_code = ft_atol(n->args[1]);
			if (exit_code == -1)
				return (s_e(data, 2), ft_putmsg_fd(EX, n->args[1], NAR, 2), 2);
			if (exit_code < 0)
				exit_code = (exit_code % 256 + 256) % 256;
		}
		clean_data(data);
		exit(exit_code);
	}
	return (exit_code);
}

int	ft_exit(t_data *data, t_cmd *node)
{
	long	exit_code;
	int		i;

	if (node->next != NULL || data->we_have_child == 1)
		return (0);
	i = 0;
	exit_code = 0;
	if (node->args[1] == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		clean_data(data);
		exit(0);
	}
	if (handle_signs(node->args[1]) != 0)
		return (s_e(data, 2), ft_putmsg_fd("exit: ", node->args[1], NAR, 2), 2);
	while (node->args[1][i] != '\0')
	{
		if (ft_isdigit(node->args[1][i]) == 0
			&& node->args[1][i] != '+' && node->args[1][i] != '-'
			&& node->args[1][i] != ' ')
			return (s_e(data, 2), ft_putmsg_fd(EX, node->args[1], NAR, 2), 2);
		i++;
	}
	exit_code = ft_exit_atol(data, node);
	return (exit_code);
}
