/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:41:26 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/16 11:37:06 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	increase_shell_lvl(t_data *data)
{
	int		val;
	char	*s;
	t_var	*lvl;

	lvl = get_env_var(data, "SHLVL");
	if (!lvl)
		set_env_var(data, "SHLVL", "1");
	val = ft_atoi(lvl->val) + 1;
	s = ft_itoa(val);
	set_env_var(data, "SHLVL", s);
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
			res[i] = ft_strjoin(temp->key, temp->val);
			if (!res[i])
				panic("strjoin");
		}
		i++;
		temp = temp->next;
	}
	res[i] = NULL;
	return (res);
}

int main(int ac, char **av, char **ev)
{
	char *line;
	t_data *data;
	int err_no;
	// char *svl_str = getenv("SHLVL");
	// if (svl_str)
	// 	shl_lvl = atoi(svl_str);
	// shl_lvl++;
	// printf("%d\n", shl_lvl);
	// t_cmd	*cmd;

//printf("1\n");
	data = init_data(ac, av, ev);
	data->err_no = 0;
	increase_shell_lvl(data);
	while (1)
	{
		line = readline("> ");
		if (ft_strlen(line) == 0)
			continue ;
		data->tokens = tokenize(line);
		data->path_arr = get_path_arr(ev);
		reorder_tokens(data);
		set_cmd_table(data);
		data->err_no = run_pipe(data, data->cmds, ev);
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