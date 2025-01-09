/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:11:41 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/04/30 14:17:47 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(char const *s)
{
	size_t	len;

	len = 0;
	while (*(s + len))
		len++;
	return (len);
}

static char	*ft_newstr(size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*str;
	char	*res;

	if (!s)
		return (NULL);
	str = ft_newstr(ft_len(s));
	if (!str)
		return (NULL);
	i = 0;
	res = str;
	while (*s)
		*str++ = f(i++, *s++);
	*str = '\0';
	return (res);
}
