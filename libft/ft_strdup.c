/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:24:46 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/24 13:21:27 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	

static size_t	len(char const *src)
{
	size_t	lngth;

	lngth = 0;
	if (!src)
		return (0);
	while (src[lngth] != '\0')
		lngth++;
	return (lngth);
}

static char	*alloc(size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_strdup(char const *src)
{
	char	*dest;
	char	*ret;

	dest = alloc(len(src));
	if (!dest)
		return (NULL);
	ret = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (ret);
}
