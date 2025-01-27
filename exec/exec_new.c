/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:39:20 by oshcheho          #+#    #+#             */
/*   Updated: 2025/01/24 13:59:17 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int execute(t_data *data, char **envp)
{
//	int res;
//	char *full_path;

//	printf("node %s \n", data->cmds->args[0]);

//	full_path = find_path(data->cmds->args[0], data->path_arr);
//	printf("f path %s \n", full_path);
	data->err_no = run_pipe(data, data->cmds, envp);
	printf("res %d \n", data->err_no);

	return (data->err_no);
}