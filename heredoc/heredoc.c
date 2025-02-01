/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:29:19 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/31 17:52:52 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include "../minishell.h"

extern sig_atomic_t g_signal;

void	end_it(t_data *data)
{
	clean_data(data);
	panic("malloc");
}

char	*random_name(t_data *data, int i)
{
	if (i % 2 == 0)
		return ft_strjoin("BROUGHT_TO_YOU_BY_STATEFARM_", ft_itoa(i));
	else
		return ft_strjoin("BROUGHT_TO_YOU_BY_CARLSJR_", ft_itoa(i));	
}

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
		return ft_strdup("?");
	}
	key = ft_substr(line, *index, end - *index);
	if (!key)
		end_it(data);
	*index = end;
	return;
}

void	expand_variable(char *line, int *index, char **exp_line, t_data *data)
{
	t_var	*env_var;
	char	*key;
	
	env_var = NULL;
	key = get_key(data, line, index);
}

void	add_to_line(char c, char *line, t_data *data)
{
	char	*temp;

	temp = NULL;
	if (line)
		temp = line;
	line = ft_strjoin(temp, &c);
	if (temp)
		free(temp);
	temp = NULL;
	if (!line)
		end_it(data);
}

char	*expand_heredoc(char *line, t_data *data)
{
	int		i;
	char	*expanded_line;
	t_var	*env_var;

	i = 0;
	env_var = NULL;
	expanded_line = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] != 32 && line[i + 1] != '\0')
			expand_variable(line, &i, &expanded_line, data);
		else
		{
			add_to_line(line[i], expanded_line, data);
			if (!line)
				return (free(expanded_line), NULL);
		}
		++i;
	}
}

void	fill_heredoc(int fd, t_redir *redir, t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc->");
		if (g_signal == SIGINT)
			break;
		if (!line)
		{
			ft_putstr_fd("minishell: warning: heredoc delimited by EOF\n", STDERR_FILENO);
            break;
		}
		if (ft_strcmp(line, redir->val) == 0)
		{
			free(line);
			break;
		}
		if (redir->expands)
			line = expand_heredoc(data, line);
		if (line)
			ft_putendl_fd(line, fd);
		free(line);
	}
}

int	open_heredoc(t_data *data, t_cmd *cmd, t_redir *redir, int i)
{
	int		fd;
	char	*filename;

	filename = random_name(data, i);
	if (!filename)
		end_it(data);
	redir->heredoc = filename;
	filename = NULL;
	fd = open(redir->heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fill_heredoc(fd, redir, data);
	close(fd);
}

void	heredoc(t_data *data)
{
	int		i;
	t_cmd	*curr;
	t_redir	*redir;

	i = 0;
	curr = NULL;
	redir = NULL;
	if (data->cmds)
		curr = data->cmds;
	while (curr)
	{
		if (curr->redir)
			redir = curr->redir;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				open_heredoc(data, curr, redir, i);
				i++;
			}
			redir = redir->next;
		}
		curr = curr->next;
	}
	set_signals(PARENT);
}
