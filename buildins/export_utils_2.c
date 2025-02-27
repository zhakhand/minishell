/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:18:17 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 12:18:17 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**fill_env_arr(t_data *data, char **res)
{
	t_var	*temp;
	char	*tmp_val;
	int		i;

	i = 0;
	temp = data->env_var;
	while (temp)
	{
		if (temp->is_valid == 1)
		{
			tmp_val = add_quotes_to_val(temp->val);
			res[i] = ft_strjoin(temp->key, tmp_val);
		}
		else
			res[i] = ft_strdup(temp->key);
		if (!res[i])
			end_it(data);
		if (tmp_val)
			free(tmp_val);
		tmp_val = NULL;
		i++;
		temp = temp->next;
	}
	res[i] = NULL;
	return (res);
}

char	**make_env_arr(t_data *data)
{
	char	**res;
	t_var	*temp;
	int		i;

	temp = data->env_var;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	res = malloc((i + 1) * sizeof(char *));
	if (!res)
		end_it(data);
	res = fill_env_arr(data, res);
	return (res);
}

int	add_to_env(char *str, t_data *data)
{
	t_var	*new_var;
	int		i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == 0)
	{
		new_var = get_env_var(data, str);
		if (!new_var)
		{
			new_var = set_env_var(data, str, "");
			new_var->is_valid = 0;
		}
		return (0);
	}
	else if (str[i] == '=' && !str[i + 1])
	{
		new_var = set_env_var(data, ft_substr(str, 0, i), "");
		new_var->is_valid = 1;
		return (0);
	}
	new_var = set_env_var(data, ft_substr(str, 0, i), str + i + 1);
	new_var->is_valid = 1;
	return (0);
}

int	check_all_symbols(char *str)
{
	int	i;
	int	flag;

	i = 0;
	if (str[0] == '_')
		i++;
	flag = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			flag = 1;
			i++;
			continue ;
		}
		if (flag == 0 && str[i] == '-')
			return (1);
		if (flag == 0)
			if (!ft_isalnum(str[i]) && str[i] != ' ' && str[i] != '_'
				&& str[i] != '"' && str[i] != '$')
				return (1);
		i++;
	}
	return (0);
}

int	check_symbols(char *str)
{
	int	res;

	if (!str)
		return (1);
	if (str[0] == '|' || str[0] == '=')
		return (1);
	if (str[0] == '_' && str[1] == '\0')
		return (1);
	if (str[0] >= '0' && str[0] <= '9')
		return (1);
	res = check_all_symbols(str);
	return (res);
}
