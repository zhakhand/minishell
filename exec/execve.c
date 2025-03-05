/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:19:36 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 12:19:36 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_full_path(char *full_path, t_cmd *cmd, char **envp, t_data *data)
{
	struct stat	sb;

	if (stat(full_path, &sb) == -1)
		return (ft_putmsg_fd("", cmd->args[0], N_F_D, data), 127);
	if (S_ISDIR(sb.st_mode))
		return (ft_putmsg_fd("", cmd->args[0], I_A_D, data), 126);
	if (access(full_path, X_OK) == -1)
		return (ft_putmsg_fd("", cmd->args[0], P_D, data), 126);
	if (execve(full_path, cmd->args, envp))
		return (perror ("execve"), 1);
	return (0);
}

char	*full_path_init(t_data *data, t_cmd *cmd, char **envp)
{
	char	*full_path;
	int		is_explicit_path;

	full_path = NULL;
	is_explicit_path = ft_strchr(cmd->args[0], '/') != NULL;
	if (is_explicit_path)
		full_path = ft_strndup(cmd->args[0], str_len(cmd->args[0]), data);
	data->path_arr = get_path_arr(envp, data);
	return (full_path);
}

int	run_execve(t_data *data, t_cmd *cmd, char **envp)
{
	struct stat		sb;

	data->full_path = full_path_init(data, cmd, envp);
	if (!data->full_path)
	{
		if (!data->path_arr || !data->path_arr[0])
		{
			if (stat(cmd->args[0], &sb) == 0)
			{
				if (access(cmd->args[0], X_OK) == -1)
					return (ft_putmsg_fd("", cmd->args[0], P_D, data), 126);
				data->full_path = \
				ft_strndup(cmd->args[0], str_len(cmd->args[0]), data);
			}
			else
				return (ft_putmsg_fd("", cmd->args[0], N_F_D, data), 127);
		}
		else
		{
			data->full_path = find_path(cmd->args[0], data->path_arr);
			if (!data->full_path)
				return (ft_putmsg_fd("", cmd->args[0], C_N_F, data), 127);
		}
	}
	return (check_full_path(data->full_path, cmd, envp, data));
}
