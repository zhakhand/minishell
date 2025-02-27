/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:17:51 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 12:17:51 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <time.h>

int	cd_home(t_data *data)
{
	char	*home;

	home = get_home(data);
	if (!home)
	{
		ft_putmsg_fd(MSH_CD, "HOME not set", "\n", data);
		return (EXIT_FAILURE);
	}
	if (chdir(home) == -1)
		perror("home: No such file or directory");
	change_old_pwd_in_env(data, data->pwd);
	change_pwd_in_env(data, getcwd(NULL, 0));
	return (0);
}

int	cd_prev(t_data *data)
{
	char	*pwd;
	char	*old_pwd;

	if (!data->old_pwd || data->old_pwd[0] == '\0')
	{
		return (ft_putmsg_fd("cd: ", O_PWD, "\n", data), EXIT_FAILURE);
	}
	pwd = ft_strdup(data->pwd);
	old_pwd = ft_strdup(data->old_pwd);
	if (!pwd || !old_pwd)
		end_it(data);
	if (chdir(old_pwd) == -1)
	{
		perror("cd");
		free(pwd);
		free(old_pwd);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(old_pwd, STDOUT_FILENO);
	change_old_pwd_in_env(data, pwd);
	change_pwd_in_env(data, getcwd(NULL, 0));
	free(pwd);
	free(old_pwd);
	return (0);
}

int	cd_up(t_data *data, t_cmd *node)
{
	struct stat	sb;
	char		*pwd;

	pwd = get_i_for_cd_up(data);
	if (stat(node->args[1], &sb) == -1)
		return (free(pwd), ft_putmsg_fd(MSH_CD, node->args[1], N_F_D, data), 1);
	if (ft_strcmp(data->pwd, "/") == 0)
		return (0);
	free(pwd);
	pwd = ft_strdup(data->pwd);
	if (!pwd)
		end_it(data);
	if (chdir(node->args[1]) == -1)
		return (free(pwd), ft_putmsg_fd("cd: ", node->args[1], N_F_D, data), 1);
	change_old_pwd_in_env(data, pwd);
	free(pwd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(pwd), ft_putmsg_fd(MSH_CD, "", N_F_D, data), 1);
	change_pwd_in_env(data, getcwd(NULL, 0));
	return (free(pwd), 0);
}

int	cd_dir(t_data *data, t_cmd *node)
{
	char		*pwd;
	struct stat	sb;

	pwd = ft_strjoin(data->pwd, node->args[1]);
	if (!pwd)
		end_it(data);
	check_abs_path(node);
	if (stat(node->args[1], &sb) == -1)
		return (free(pwd), ft_putmsg_fd(MSH_CD, node->args[1], N_F_D, data), 1);
	if (!S_ISDIR(sb.st_mode))
		return (free(pwd), ft_putmsg_fd(MSH_CD, node->args[1], N_A_D, data), 1);
	if (access(node->args[1], X_OK) == -1)
		return (free(pwd), ft_putmsg_fd(MSH_CD, node->args[1], P_D, data), 126);
	if (chdir(node->args[1]) == -1)
		return (free(pwd), ft_putmsg_fd(MSH_CD, node->args[1], F_C_D, data), 1);
	change_old_pwd_in_env(data, data->pwd);
	change_pwd_in_env(data, getcwd(NULL, 0));
	return (free(pwd), 0);
}

int	changedir(t_data *data, t_cmd *node)
{
	int	res;

	res = -1;
	if (data->child_start == 1)
		return (0);
	check_abs_path(node);
	if (node->args && node->args[1] && node->args[2])
		return (ft_putmsg_fd(MSH, "cd", T_M_A, data), EXIT_FAILURE);
	if (!node->next)
	{
		if (node->args[1] == NULL || ft_strncmp(node->args[1], "~", 2) == 0)
			res = cd_home(data);
		else if (ft_strncmp(node->args[1], "..", 2) == 0
			|| (ft_strncmp(node->args[1], "../", 3) == 0))
			res = cd_up(data, node);
		else if (ft_strncmp(node->args[1], "-", 1) == 0)
			res = cd_prev(data);
		else
			res = cd_dir(data, node);
	}
	return (res);
}
