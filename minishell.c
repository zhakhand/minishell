/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:41:26 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/27 15:15:17 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

sig_atomic_t	g_signal = 0;

char	**fill_temp(char **res, t_data *data)
{
	int		i;
	char	*tmp;
	t_var	*temp;

	i = 0;
	temp = data->env_var;
	while (temp)
	{
		tmp = NULL;
		if (temp->is_valid == 1)
		{
			tmp = ft_strjoin(temp->key, "=");
			res[i] = ft_strjoin(tmp, temp->val);
			if (tmp)
				free(tmp);
			if (!res[i])
				end_it(data);
		}
		i++;
		temp = temp->next;
	}
	res[i] = NULL;
	return (res);
}

char	**make_env(t_data *data)
{
	t_var	*temp;
	char	**res;
	char	*tmp;
	int		i;

	temp = data->env_var;
	tmp = NULL;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	res = ft_calloc((i + 1), sizeof(char *));
	if (!res)
		end_it(data);
	res = fill_temp(res, data);
	if (!res)
		end_it(data);
	return (res);
}

void	tokens_and_heredoc(t_data *data)
{
	t_cmd	*cmd;

	cmd = NULL;
	data->env = make_env(data);
	data->tokens = tokenize(data);
	if (data->tokens && reorder_tokens(data) == 0)
	{
		set_cmd_table(data);
		set_signals(HEREDOC);
		if (data->cmds && heredoc(data) == 0)
		{
			set_signals(PARENT);
			cmd = data->cmds;
			run_pipe(data, cmd, data->env);
		}
	}
}

void	make_line(t_data *data)
{
	char	*prompt;

	data->env = NULL;
	prompt = ft_strjoin(data->pwd, " $ ");
	if (!prompt)
		end_it(data);
	data->line = readline(prompt);
	add_history(data->line);
	free(prompt);
	prompt = NULL;
}

int	main(int ac, char **av, char **ev)
{
	t_data	*data;
	int		err_no;

	data = init_data(ac, av, ev);
	while (1)
	{
		set_signals(PARENT);
		make_line(data);
		if (data->line == 0)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (ft_strlen(data->line) == 0)
			continue ;
		tokens_and_heredoc(data);
		reset_data(data);
	}
	err_no = data->err_no;
	clean_data(data);
	clear_history();
	return (err_no);
}
