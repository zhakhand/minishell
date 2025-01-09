/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:38:09 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/09 19:46:23 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_built_in(char *cmd)
{
	if (cmd)
		return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 \
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 \
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 \
	|| ft_strcmp(cmd, "exit") == 0);
	return (0);
}

void	set_built_in(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		cmd->built_in = ECH;
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		cmd->built_in = CD;
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		cmd->built_in = PWD;
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		cmd->built_in = EXPORT;
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		cmd->built_in = UNSET;
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		cmd->built_in = ENV;
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		cmd->built_in = EXIT;
}

void	check_built_in(t_data *data)
{
	t_cmd	*curr;
	
	if (!data->cmds)
		return;
	curr = data->cmds;
	while (curr)
	{
		if (is_built_in(curr->cmd))
			set_built_in(curr);
		curr = curr->next;
	}
}