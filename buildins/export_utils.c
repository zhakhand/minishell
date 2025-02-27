/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:18:23 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 12:18:23 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_to_env_end_helper(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	return (i);
}

int	add_to_env_end(char *str, t_data *data)
{
	t_var	*new_var;
	int		i;

	new_var = NULL;
	i = add_to_env_end_helper(str);
	if (str[i] == 0)
	{
		new_var = get_env_var(data, str);
		if (!new_var)
		{
			new_var = set_env_var \
			(data, ft_strndup(str, str_len(str), data), "");
			new_var->is_valid = 0;
		}
		return (0);
	}
	else if (str[i] == '=' && !str[i + 1])
	{
		new_var = set_env_var(data, ft_strndup(str, i, data), "");
		new_var->is_valid = 1;
		return (0);
	}
	new_var = set_env_var(data, ft_strndup(str, i, data), str + i + 1);
	new_var->is_valid = 1;
	return (0);
}

char	*add_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	new_str = malloc((len + 3) * sizeof(char));
	if (!new_str)
		panic("malloc");
	while (str[i] != '=')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '=';
	new_str[i + 1] = '"';
	i = i + 2;
	while (str[i - 1] != '\0')
	{
		new_str[i] = str[i - 1];
		i++;
	}
	new_str[i] = '"';
	new_str[i + 1] = '\0';
	return (new_str);
}

char	*add_quotes_to_val(char *str)
{
	char	*new_str;
	int		i;
	int		len;

	len = ft_strlen(str);
	new_str = malloc((len + 4) * sizeof(char));
	if (!new_str)
		panic("malloc");
	new_str[0] = '=';
	new_str[1] = '"';
	i = 2;
	while (str[i - 2] != '\0')
	{
		new_str[i] = str[i - 2];
		i++;
	}
	new_str[i] = '"';
	new_str[i + 1] = '\0';
	return (new_str);
}

char	**sort_env(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (arr[i] != NULL)
	{
		j = i + 1;
		while (arr[j] != NULL)
		{
			if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i])) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (arr);
}
