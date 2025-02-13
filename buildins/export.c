/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:18:29 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 12:18:29 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_open_quotes(char *str)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			open++;
		i++;
	}
	if (open % 2 != 0)
		return (1);
	return (0);
}

char	*remove_quotes_in_the_middle(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc((ft_strlen(str) - 1) * sizeof(char));
	if (!new_str)
		panic("malloc");
	while (str[i] != '\0')
	{
		if (str[i] != '"')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*if_one_quote(char *str)
{
	char	*new_str;
	char	*buffer;
	int		open_quotes;

	open_quotes = check_open_quotes(str);
	while (open_quotes != 0)
	{
		buffer = readline("> ");
		if (!buffer)
			return (NULL);
		new_str = ft_strjoin(str, buffer);
		if (!new_str)
			panic("strjoin");
		free(str);
		str = NULL;
		str = new_str;
		open_quotes = check_open_quotes(str);
		free(buffer);
		buffer = NULL;
	}
	return (str);
}

void	export_no_args(t_data *data)
{
	int		i;
	char	**tmp;

	tmp = make_env_arr(data);
	tmp = sort_env(tmp);
	i = 0;
	while (tmp[i] != NULL)
	{
		if (tmp[i][0] != '_')
			ft_putmsg_fd("declare -x ", tmp[i], "\n", STDOUT_FILENO);
		i++;
	}
	free_args(&tmp);
	tmp = NULL;
}

int	ft_export(t_data *data, t_cmd *node)
{
	int	i;

	if (node->next != NULL)
		return (0);
	if (node->args[1] == NULL)
		return (export_no_args(data), 0);
	i = 1;
	if (check_symbols(node->args[1]) == 1)
		return (ft_putmsg_fd("export: `", node->args[1], NVI, 2), 1);
	while (node->args[i] != NULL)
	{
		if (ft_strchr(node->args[i], '=') != NULL)
		{
			if (check_open_quotes(node->args[i]) == 1)
			{
				node->args[i] = if_one_quote(node->args[i]);
				if (!node->args[i])
					return (0);
			}
		}
		add_to_env_end(node->args[i], data);
		i++;
	}
	return (0);
}
