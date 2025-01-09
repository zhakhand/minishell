/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:59:30 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/07/22 11:22:36 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	gnl_free(char **a)
{
	if (a && *a)
	{
		free(*a);
		*a = NULL;
	}
}

char	*gnl_strncpy(char *d, char *s, int l)
{
	int	i;

	i = 0;
	if (l == 0)
		return (d);
	if (!d || !s)
		return (NULL);
	while (i < l && s[i])
	{
		d[i] = s[i];
		i++;
	}
	while (i < l)
	{
		d[i++] = '\0';
	}
	return (d);
}

char	*gnl_strcat(char *d, char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!d || !s)
		return (NULL);
	while (d[i] != '\0')
		i++;
	while (s[j] != '\0')
		d[i++] = s[j++];
	d[i] = '\0';
	return (d);
}

char	*gnl_strchr(char	*s, char c)
{
	if (!s || !c)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return ((char *) s);
		s++;
	}
	if (c == '\0')
		return ((char *) s);
	return (NULL);
}

int	gnl_strlen(char *s)
{
	int	l;

	l = 0;
	if (!s)
		return (0);
	while (s[l])
		l++;
	return (l);
}
