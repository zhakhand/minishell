/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:19:08 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 12:19:08 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_slash(char ***path_arr)
{
	int		i;
	char	*new_path;

	i = 0;
	while ((*path_arr)[i])
	{
		if ((*path_arr)[i][ft_strlen((*path_arr)[i]) - 1] != '/')
		{
			new_path = ft_strjoin((*path_arr)[i], "/");
			free((*path_arr)[i]);
			(*path_arr)[i] = new_path;
		}
		i++;
	}
}

char	**fill_path_arr(char **envp)
{
	int		i;
	char	**path_arr;

	path_arr = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			if (envp[i][5] == '\0')
				return (NULL);
			path_arr = ft_split(envp[i], ':');
			if (!path_arr)
				return (NULL);
			break ;
		}
		i++;
	}
	return (path_arr);
}

int	get_path_line(char **envp)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**get_path_arr(char **envp)
{
	int		i;
	char	**path_arr;
	char	*trimmed_path;

	i = 0;
	path_arr = NULL;
	trimmed_path = NULL;
	i = get_path_line(envp);
	if (i == -1)
		return (NULL);
	path_arr = fill_path_arr(envp);
	if (!path_arr)
		return (NULL);
	if (envp[i][5] != '\0')
		trimmed_path = ft_strdup(path_arr[0] + 5);
	if (trimmed_path)
	{
		free(path_arr[0]);
		path_arr[0] = trimmed_path;
	}
	add_slash(&path_arr);
	return (path_arr);
}

char	*find_path(char *cmd, char **path)
{
	int		i;
	char	*res;

	res = NULL;
	if (ft_strncmp(cmd, "./", 2) == 0)
	{
		res = ft_substr(cmd, 2, ft_strlen(cmd) - 2);
		if (access(res, F_OK) == 0)
			return (res);
	}
	else if (ft_strncmp(cmd, "/", 1) == 0
		&& access(cmd, F_OK) == 0)
		return (cmd);
	else
	{
		i = -1;
		while (path[++i] != NULL)
		{
			res = ft_strjoin(path[i], cmd);
			if (access(res, F_OK) == 0)
				return (res);
			free(res);
		}
	}
	return (NULL);
}
