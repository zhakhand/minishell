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

void	ft_putmsg_fd(char *msg1, char *msg2, char *msg3, int fd)
{
	char	*msg;
	char	*temp;

	msg = ft_strdup(msg1);
	if (!msg)
		panic("strdup");
	temp = ft_strjoin(msg, msg2);
	free(msg);
	msg = NULL;
	if (!temp)
		panic("strjoin");
	msg = ft_strjoin(temp, msg3);
	free(temp);
	temp = NULL;
	if (!msg)
		panic("strjoin");
	ft_putstr_fd(msg, fd);
	free(msg);
	msg = NULL;
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
		ft_putmsg_fd(MSH, cmd->args[0], C_N_F, STDERR_FILENO);
		return (1);
	}
	return (0);
}
