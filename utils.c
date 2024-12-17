/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:52:57 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/12/16 20:52:57 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	str_len(char *str)
{
	int	i;

	i = 0;			
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;	

	i = 0;
	while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0')
		i++;
	return (str1[i] - str2[i]);
}

int	is_sep(char c)
{
	if (c == '|' || c == '$' || c == '<' || c == '>' || c == '\'' || c == '\"' || c == 32)
		return (1);
	return (0);
}

char	*ft_strndup(char *str, int len)
{
	char	*retStr;
	int		i;

	i = -1;
	retStr = malloc(sizeof(char *) * len + 1);
	if (!retStr)
		exit(2);
	while (++i < len && str[i] != '\0')
		retStr[i] = str[i];
	retStr[i] = '\0';
	return (retStr);
}

char	*str_cpy(char *dest, char const *src)
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
		return (NULL);
	}
	res = new_str(str_len(s1) + str_len(s2));
	if (!res)
		return (NULL);
	str_cpy(res, s1);
	str_cpy(res + str_len(s1), s2);
	return (res);
}