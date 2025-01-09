/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:34:00 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/04/24 16:37:35 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *src, char const *str, size_t n)
{
	size_t	i;

	if (!src && !n)
		return (NULL);
	if (!*str)
		return ((char *)src);
	while (*src && n--)
	{
		i = 0;
		while (*(src + i) == *(str + i) && (str[i] != '\0') && i <= n)
		{
			if (str[i + 1] == '\0')
				return ((char *)src);
			i++;
		}
		src++;
	}
	return (NULL);
}
