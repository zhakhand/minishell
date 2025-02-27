/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:29:19 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/02/27 13:51:24 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include "../minishell.h"

extern sig_atomic_t g_signal;

char	*random_name(t_data *data, int i)
{
	char	*res;
	char	*num;

	res = NULL;
	num = ft_itoa(i);
	if (!num)
		end_it(data);
	if (i % 3 == 0)
		res = ft_strjoin("here", num);
	else if (i % 3 == 1)
		res = ft_strjoin("there", num);
	else
		res = ft_strjoin("nowhere", num);
	free(num);
	if (!res)
		end_it(data);
	return (res);
}

void	add_to_line(char c, char **line, t_data *data)
{
	char	*temp;
	char	str[2];

	temp = NULL;
	str[0] = c;
	str[1] = '\0';
	if (*line)
		temp = *line;
	*line = ft_strjoin(temp, str);
	if (temp)
		free(temp);
	temp = NULL;
	if (!*line)
		end_it(data);
}

int	fill_heredoc(int fd, t_redir *redir, t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
			return (close(fd), -1);
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
		if (redir->expands && ft_strchr(line, '$'))
			line = expand_heredoc(line, data);
		if (line)
			ft_putendl_fd(line, fd);
		free(line);
	}
	return (0);
}

int	open_heredoc(t_data *data, t_redir *redir, int i)
{
	int		fd;
	char	*filename;

	filename = random_name(data, i);
	if (!filename)
		end_it(data);
	redir->heredoc = ft_strndup(filename, str_len(filename), data);
	free(filename);// leaks?
	filename = NULL;
	fd = open(redir->heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fill_heredoc(fd, redir, data) == -1)
		return (-1);
	close(fd);
	return (0);
}

int	heredoc(t_data *data)
{
	int		i;
	t_cmd	*curr;
	t_redir	*redir;

	i = 0;
	curr = data->cmds;
	redir = NULL;
	while (curr)
	{
		if (curr->redir)
			redir = curr->redir;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (open_heredoc(data, redir, i) == -1)
					return (-1);
				i++;
			}
			redir = redir->next;
		}
		curr = curr->next;
	}
	return (0);
}
