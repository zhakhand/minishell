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

#include "../parser.h"
#include "../minishell.h"

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
	if ((!str1 || !str2))
		return (1);
	while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0')
		i++;
	return (str1[i] - str2[i]);
}

int	is_sep(char c)
{
	if (c == '|' || c == '$' || c == '<' \
	|| c == '>' || c == '\'' || c == '\"' || c == 32 || c == 9)
		return (1);
	return (0);
}

char	*ft_strndup(char *str, int len, t_data *data)
{
	char	*ret_str;
	int		i;

	i = -1;
	ret_str = ft_calloc(len, sizeof(char));
	if (!ret_str)
		end_it(data);
	while (++i < len && str[i] != '\0')
		ret_str[i] = str[i];
	ret_str[i] = '\0';
	return (ret_str);
}

void	free_and_null(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}
