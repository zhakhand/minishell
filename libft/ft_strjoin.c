/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:36:29 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/09 15:37:07 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	str_len(char const *s)
{
	size_t	len;

	len = 0;
	if (!s || !*s)
		return (0);
	while (*(s + len))
		len++;
	return (len);
}

static char	*str_cpy(char *dest, char const *src)
{
	while (*src)
		*dest++ = *src++;
	return (dest);
}

static	char	*new_str(size_t len)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	*(res + len) = '\0';
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;

	if (!s1 || !s2)
	{
		if (s1 && !s2)
			return ft_strdup(s1);
		if (!s1 && s2)
			return ft_strdup(s2);
		if (!s1 && !s2)
			return NULL;
	}
	res = new_str(str_len(s1) + str_len(s2));
	if (!res)
		return (NULL);
	str_cpy(res, s1);
	str_cpy(res + str_len(s1), s2);
	return (res);
}
