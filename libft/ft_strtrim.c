/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:28:38 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/04/25 15:05:11 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	str_len(char const *str)
{
	size_t	len;

	len = 0;
	while (*(str + len))
		len++;
	return (len);
}

static int	in_set(char const *set, char const c)
{
	size_t	i;

	i = 0;
	if (!set)
		return (0);
	while (*(set + i))
	{
		if (*(set + i) == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*str_new(size_t len)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	begin;
	size_t	end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	begin = 0;
	end = str_len(s1);
	while (*(s1 + begin) && in_set(set, *(s1 + begin)))
		begin++;
	while (end > begin && in_set(set, *(s1 + (end - 1))))
		end--;
	res = str_new(end - begin);
	if (!res)
		return (NULL);
	i = 0;
	while ((i + begin) < end)
	{
		*(res + i) = *(s1 + begin + i);
		i++;
	}
	*(res + i) = '\0';
	return (res);
}
