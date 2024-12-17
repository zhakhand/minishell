/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:14:42 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/04/24 16:14:44 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	all_zero(void *s, size_t n)
{
	while (n--)
		*(char *)s++ = 0;
}

void	*ft_calloc(size_t count, size_t n)
{
	void	*mem;

	if (count && n && (count > (UINT_MAX / n)))
		return (NULL);
	mem = malloc(count * n);
	if (!mem)
		return (NULL);
	all_zero(mem, count * n);
	return (mem);
}
