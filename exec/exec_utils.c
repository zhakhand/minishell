/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:33:22 by oshcheho          #+#    #+#             */
/*   Updated: 2025/01/11 13:33:23 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	panic(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_putmsg_fd(char *msg1, char *msg2, char *msg3, t_data *data)
{
	char	*msg;
	char	*temp;

	msg = ft_strdup(msg1);
	if (!msg)
		end_it(data);
	temp = ft_strjoin(msg, msg2);
	free(msg);
	msg = NULL;
	if (!temp)
		end_it(data);
	msg = ft_strjoin(temp, msg3);
	free(temp);
	temp = NULL;
	if (!msg)
		end_it(data);
	ft_putstr_fd(msg, data->out_fd);
	free(msg);
	msg = NULL;
	data->out_fd = 2;
}

int	ft_edge_cases(t_data *data, t_cmd *cmd)
{
	if (cmd->args_count == 0 || !cmd->args)
		return (0);
	if (!cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "") == 0
		|| ft_strcmp(cmd->args[0], ".") == 0
		|| ft_strcmp(cmd->args[0], "//") == 0
		|| ft_strcmp(cmd->args[0], "..") == 0
		|| ft_strcmp(cmd->args[0], "~") == 0)
	{
		data->err_no = 127;
		ft_putmsg_fd(MSH, cmd->args[0], C_N_F, data);
		return (1);
	}
	return (0);
}

int	wait_last_pid(t_data *data, int count)
{
	int	i;
	int	status;

	i = 0;
	while (i < count)
	{
		if (data->pid[i] == -1)
		{
			i++;
			continue ;
		}
		if (waitpid(data->pid[i], &status, 0) == -1)
		{
			clean_data(data);
			panic("waitpid");
		}
		i++;
	}
	return (status);
}

int	init_parent_vars(t_data *data, t_cmd *cmd)
{
	int	prev_fd;

	data->child_start = 0;
	cmd->fds[0] = STDIN_FILENO;
	cmd->fds[1] = STDOUT_FILENO;
	prev_fd = STDIN_FILENO;
	if (cmd->next != NULL)
		data->we_have_child = 1;
	return (prev_fd);
}
