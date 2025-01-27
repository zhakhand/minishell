/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:28:53 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/12/19 12:34:20 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wrdlen(char const *str, char c)
{
	size_t	len;

	len = 0;
	while (*(str + len) && *(str + len) != c)
		len++;
	return (len);
}

static size_t	ft_wrdcount(char const *str, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (*(str + i))
	{
		if (*(str + i) != c)
		{
			count++;
			while (*(str + i) && (*(str + i) != c))
				i++;
		}
		else if (*(str + i) == c)
			i++;
	}
	return (count);
}

void	free_arr(char **array, size_t i)
{
	while (i > 0)
	{
		i--;
		free(*(array + i));
	}
	free(array);
}

static char	**fill_array(char **array, char const *s, char c, size_t words)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < words)
	{
		while (*(s + j) && (*(s + j) == c))
			j++;
		*(array + i) = ft_substr(s, j, ft_wrdlen(&*(s + j), c));
		if (!*(array + i))
		{
			free_arr(array, i);
			return (NULL);
		}
		while (*(s + j) && (*(s + j) != c))
			j++;
		i++;
	}
	*(array + i) = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	words;

	words = ft_wrdcount(s, c);
	if (!s)
	{
		return (NULL);
	}
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return ((NULL));
	array = fill_array(array, s, c, words);
	return (array);
}
