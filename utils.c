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

int	strLen(char *str)
{
	int	i;

	i = 0;			
	while (str[i] != '\0')
		i++;
	return (i);
}

int	strCmp(char *str1, char *str2)
{
	int	i;	

	i = 0;
	while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0')
		i++;
	return (str1[i] - str2[i]);
}

int	isSep(char c)
{
	if (c == '|' || c == '$' || c == '<' || c == '>' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

char	*strNDup(char *str, int len)
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