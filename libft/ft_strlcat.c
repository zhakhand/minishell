/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:27:35 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/04/24 16:30:18 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len(char const *src)
{
	size_t	lngth;

	lngth = 0;
	while (src[lngth] != '\0')
		lngth++;
	return (lngth);
}

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t		dest_len;
	size_t		total_len;
	const char	*str;

	if ((!dest || !src) && !n)
		return (0);
	str = src;
	dest_len = 0;
	while (dest[dest_len] != '\0' && dest_len < n)
		dest_len++;
	if (dest_len < n)
		total_len = dest_len + len(str);
	else
		return (n + len(str));
	while (*str && (dest_len + 1) < n)
	{
		dest[dest_len] = *str++;
		dest_len++;
	}
	dest[dest_len] = '\0';
	return (total_len);
}
