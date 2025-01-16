/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:41:26 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/16 15:56:49 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

sig_atomic_t g_signal = 0;

void	increase_shell_lvl(t_data *data)
{
	int		val;
	char	*s;
	t_var	*lvl;

	lvl = get_env_var(data, "SHLVL");
	if (!lvl)
		lvl = set_env_var(data, ft_strdup("SHLVL"), "0");
	val = ft_atoi(lvl->val) + 1;
	s = ft_itoa(val);
	set_env_var(data, "SHLVL", s);
	free(s);
	//printf("SHLVL= %s\n", lvl->val);
}

char **make_env(t_data *data)
{
	char **res;
	t_var *temp;
	int i;

	temp = data->env_var;

	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	res = malloc((i + 1) * sizeof(char *));
	if (!res)
		panic("malloc");
	i = 0;
	temp = data->env_var;
	while (temp)
	{
		if (temp->is_valid == 1)
		{
			res[i] = ft_strjoin(temp->key, "=");
			res[i] = ft_strjoin(res[i], temp->val);
			if (!res[i])
				panic("strjoin");
		}
		i++;
		temp = temp->next;
	}
	res[i] = NULL;
	return (res);
}

void	sighandler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDIN_FILENO, "\n", 2);
		rl_on_new_line();
		//rl_replace_line("", 0);
		//rl_redisplay();
		g_signal = signal;
	}
}

int main(int ac, char **av, char **ev)
{
	char *line;
	t_data *data;
	int err_no;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandler);
	data = init_data(ac, av, ev);
	data->err_no = 0;
	increase_shell_lvl(data);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strlen(line) == 0)
			continue ;
		data->tokens = tokenize(line);
		data->path_arr = get_path_arr(ev);
		reorder_tokens(data);
		set_cmd_table(data);
		data->err_no = run_pipe(data, data->cmds, make_env(data));
		free_tokens(data->tokens);
		free_cmds(data->cmds);
		add_history(line);
		free(line);
		//break;
	}


//	print_cmd_table(data->cmds);
	err_no = data->err_no;
	clean_data(data);
	return (err_no);

}