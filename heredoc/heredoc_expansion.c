/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:31:25 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/02/10 06:15:03 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include "../minishell.h"

char	*get_key(t_data *data, char *line, int *index)
{
	int		end;
	char	*key;

	key = NULL;
	end = *index + 1;
	while (ft_isalnum(line[end]) || line[end] == '_')
		end++;
	if (end - *index == 1 && line[end] == '?')
	{
		*index = end;
		key = ft_strdup("$?");
		if (!key)
			end_it(data);
		return (key);	
	}
	key = ft_strndup(line + *index, end - *index);
	if (!key)
		end_it(data);
	*index = end;
	return (key);
}

void	expand_error(t_data *data, char **exp_line)
{
	char	*temp1;
	char	*temp2;

	temp1 = NULL;
	temp2 = NULL;
	temp1 = ft_itoa(data->err_no);
	if (!temp1)
		end_it(data);
	temp2 = *exp_line;
	*exp_line = ft_strjoin(temp2, temp1);
	free(temp1);
	free(temp2);
	if (!*exp_line)
		end_it(data);
}

void	expand_variable(char *line, int *index, char **exp_line, t_data *data)
{
	t_var	*env_var;
	char	*temp;
	char	*key;
	
	env_var = NULL;
	temp = NULL;
	temp = *exp_line;
	if (line[*index + 1] == 32 || line[*index + 1] == '\0')
	{
		*exp_line = ft_strjoin(temp, "$");
		return free(temp);
	}
	key = get_key(data, line, index);
	if (ft_strcmp(key, "$?") == 0)
	{
		free(key);
		key = NULL;
		return expand_error(data, exp_line);
	}
	env_var = get_env_var(data, key + 1);
	if (!env_var)
		*exp_line = ft_strjoin(temp, "");
	else
		*exp_line = ft_strjoin(temp, env_var->val);
	free(temp);
	free(key);
	if (!*exp_line)
		end_it(data);
	(*index)--;
}

char	*expand_heredoc(char *line, t_data *data)
{
	int		i;
	char	*expanded_line;

	i = 0;
	expanded_line = ft_strdup("");
	if (!expanded_line)
		end_it(data);
	while (line[i] != '\0')
	{
		if (line[i] == '$' && line[i + 1] != '\0')
			expand_variable(line, &i, &expanded_line, data);
		else
		{
			add_to_line(line[i], &expanded_line, data);
			if (!line)
				return (free(expanded_line), NULL);
		}
		++i;
	}
	return (free(line), expanded_line);
}
