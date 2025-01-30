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

int is_valid_exit_code(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int handle_signs(char *str)
{
	int i;
	int res;

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
//		printf("i = %c\n", str[i]);
		if (!ft_isdigit(str[i]) && str[i] != ' ')
			res = 1;
		if (str[i] == ' ' && ft_isdigit(str[i + 1]))
			res = 1;
		i++;
	}
	return (res);
}

long ft_atol(const char *str)
{
	int i;
	long res;
	int sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
        i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
    while (str[i] && ft_isdigit(str[i]))
    {
//		printf("res = %ld\n", res*sign);
		if(res ==922337203685477580 && (str[i] - '0') == 8 && sign == -1)
			return (0);
        if (res > (LONG_MAX / 10) || (res == (LONG_MAX / 10) && (str[i] - '0' > (LONG_MAX % 10))))
        {
            return (-1); // Overflow: return -1, Underflow: return 0
        }
        res = res * 10 + (str[i] - '0');
        i++;
    }
		return (res * sign);
}

int ft_exit(t_data *data, t_cmd *node)
{
	long exit_code;
	int i;

	i = 0;
	exit_code = 0;
	if (node->args[1] == NULL)
	{
		clean_data(data);
//		system("ls -l /proc/self/fd"); // List open file descriptors

		exit(0);
	}
		if (handle_signs(node->args[1]) != 0)
			// || (node->args[1][i] == '+' && node->args[1][i + 1] == '\0')
			// || (node->args[1][i] == '-' && node->args[1][i + 1] == '\0')))
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(node->args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			data->err_no = 2;
			return (2);
		} 
	while (node->args[1][i] != '\0')
	{	
//			printf("node->args[1][i] = '%c'\n", node->args[1][i]);
		// while (node->args[1][i] == ' ')
		// 	i++;
		if (ft_isdigit(node->args[1][i]) == 0 
		&& node->args[1][i] != '+' && node->args[1][i] != '-' && node->args[1][i] != ' ')
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(node->args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			data->err_no = 2;
			return (2);
		}
		i++;
	}

	if (node->args[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		data->err_no = 1;
		return (1);
	}
	else
	{
		if (ft_strcmp(node->args[1], "-1") == 0)
			exit_code = 255;
		else
		{
		exit_code = ft_atol(node->args[1]);
		if (exit_code == -1)
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(node->args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			data->err_no = 2;
			return (2);
		}
		if (exit_code < 0)
//			exit_code = 256 + exit_code;
			exit_code = (exit_code % 256 + 256) % 256;
		}
//printf("exit  %d \n", exit_code);
		clean_data(data);
		exit(exit_code);
	}
	return (exit_code);
}