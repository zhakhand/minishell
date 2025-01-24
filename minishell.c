/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:41:26 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/24 15:30:28 by oshcheho         ###   ########.fr       */
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
	char *tmp;
	t_var *temp;
	int i;

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
		panic("malloc");
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

void	print_tokens(t_data *data)
{
	t_token *curr;

	curr = NULL;
	if (data->tokens)
		curr = data->tokens;
	while (curr)
	{
		printf("[%s]", curr->val);
		curr = curr->next;
	}
}

int main(int ac, char **av, char **ev)
{
	char *line;
	char *prompt;
	t_cmd *cmd;
//	char *prompt;
	t_data *data;
	int err_no;
	char **env;
	

	// t_cmd	*cmd;

//printf("1\n");
	data = init_data(ac, av, ev);
	data->err_no = 0;
	while (1)
	{
		// if (isatty(fileno(stdin)))
		// 	line = readline("> ");
		// else
		// {
		// 	char *pr;
		// 	pr = get_next_line(fileno(stdin));
		// 	line = ft_strtrim(pr, "\n");
		// 	free(pr);
		// }
		cmd = NULL;
		env = NULL;
		prompt = ft_strjoin(data->pwd, " $ ");
		if (!prompt)
			panic("strjoin");
		line = readline(prompt);
		free(prompt);
		prompt = NULL;
		if (line == 0)
			break ;
		if (ft_strlen(line) == 0)
			continue ;
		data->tokens = tokenize(line);
		reorder_tokens(data);
		set_cmd_table(data);
		env = make_env(data);
		//data->env_arr = make_env(data);
		// if (!data->env_arr)
		// 	panic("malloc");
		data->path_arr = get_path_arr(env);
		cmd = data->cmds;
		run_pipe(data, cmd, env);
		//data->err_no = run_pipe(data, data->cmds, ev);
		// free_tokens(data->tokens);
		// free_cmds(data->cmds);
		add_history(line);
		free(line);
		if (env)
			free_args(env);
		reset_data(data);
//		clean_data(data);
	
	//	break;
	}


//	print_cmd_table(data->cmds);
	err_no = data->err_no;
	clean_data(data);
	return (err_no);

}