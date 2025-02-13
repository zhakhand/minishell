/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:17:43 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 12:17:43 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_pwd_in_env(t_data *data, char *pwd)
{
	t_var	*temp;

	temp = data->env_var;
	while (temp)
	{
		if (ft_strncmp(temp->key, "PWD", 4) == 0)
		{
			free(temp->val);
			temp->val = ft_strdup(pwd);
			if (!temp->val)
				return (EXIT_FAILURE);
		}
		temp = temp->next;
	}
	free(data->pwd);
	data->pwd = ft_strdup(pwd);
	free(pwd);
	return (0);
}

int	change_old_pwd_in_env(t_data *data, char *pwd)
{
	t_var	*temp;

	temp = data->env_var;
	while (temp)
	{
		if (ft_strncmp(temp->key, "OLDPWD", 7) == 0)
		{
			free(temp->val);
			temp->val = ft_strdup(pwd);
			temp->is_valid = 1;
			if (!temp->val)
				return (EXIT_FAILURE);
		}
		temp = temp->next;
	}
	free(data->old_pwd);
	data->old_pwd = ft_strdup(pwd);
	return (0);
}

int	get_old_pwd(t_data *data)
{
	t_var	*temp;

	temp = data->env_var;
	while (temp)
	{
		if (ft_strncmp(temp->key, "OLDPWD", 6) == 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

char	*get_home(t_data *data)
{
	t_var	*temp;

	temp = data->env_var;
	while (temp)
	{
		if (ft_strncmp(temp->key, "HOME", 4) == 0)
			return (temp->val);
		temp = temp->next;
	}
	return (NULL);
}

void	check_abs_path(t_cmd *node)
{
	if (node->args[1])
	{
		if (node->args[1][0] == '/')
			node->abs_path = 1;
		else
			node->abs_path = 0;
	}
}
