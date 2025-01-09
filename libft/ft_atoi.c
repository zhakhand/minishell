/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:03:48 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/05/01 13:25:34 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	if (c == 32 || (c > 8 && c < 14))
		return (1);
	return (0);
}

static int	is_num(char c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	ft_atoi(char const *str)
{
	int		result;
	int		sign;
	long	last;

	result = 0;
	sign = 1;
	last = 0;
	while (is_space(*str))
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			sign *= -1;
		str++;
	}
	while (is_num(*str))
	{
		if (last != (last * 10 + *str - '0') / 10)
			return ((sign >= 0) * -1);
		last = last * 10 + *str - '0';
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}
