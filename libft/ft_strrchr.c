/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:37:45 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/04/24 16:39:28 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *str, char c)
{
	char const	*found;

	found = NULL;
	while (*str)
	{
		if (*str == c)
			found = str;
		str++;
	}
	if (*str == c)
		return ((char *)str);
	return ((char *)found);
}
