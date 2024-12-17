/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:48:14 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/04/30 14:09:31 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_numlen(int n)
{
	size_t	len;

	len = 0;
	if (n < 1)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static unsigned int	ft_abs(int n)
{
	unsigned int	abs;

	abs = 1;
	if (n < 0)
		abs *= -n;
	else
		abs *= n;
	return (abs);
}

static char	*ft_newstr(size_t len)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_itoa(int n)
{
	char			*arg;
	int				sign;
	size_t			len;
	unsigned int	num;

	sign = 0;
	len = ft_numlen(n);
	num = ft_abs(n);
	if (n < 0)
		sign = 1;
	arg = ft_newstr(len);
	if (!arg)
		return (NULL);
	*(arg + len) = '\0';
	while (len--)
	{
		*(arg + len) = 48 + (num % 10);
		num /= 10;
	}
	if (sign == 1)
		*arg = '-';
	return (arg);
}
