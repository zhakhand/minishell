/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:39:20 by oshcheho          #+#    #+#             */
/*   Updated: 2025/01/13 14:00:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int execute(t_data *data, char **envp)
{
	int res;
//	char *full_path;

//	printf("path %s \n", data->path);
//	printf("node %s \n", data->cmds->args[0]);

//	full_path = find_path(data->cmds->args[0], data->path_arr);
//	printf("f path %s \n", full_path);
	res = run_pipe(data, data->cmds, envp);

	return (res);
}