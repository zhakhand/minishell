/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:15:45 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/04/24 19:01:09 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size(char const *s)
{
	size_t	len;

	len = 0;
	while (*(s + len))
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	char	*ret;

	if (!s)
		return (NULL);
	if (start > size(s))
	{
		sub = (char *)malloc(sizeof(char) * 1);
		if (!sub)
			return (NULL);
		*sub = '\0';
		return (sub);
	}
	else if (len > size(s) - start)
		len = size(s) - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	s += start;
	ret = sub;
	*(sub + len) = '\0';
	while (*s && len--)
		*sub++ = *s++;
	sub = NULL;
	return (ret);
}
