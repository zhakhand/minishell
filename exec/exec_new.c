/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:39:20 by oshcheho          #+#    #+#             */
/*   Updated: 2025/01/11 14:01:12 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int execute(t_data *data)
{
	char *full_path;

	printf("path %s \n", data->path);
	printf("node %s \n", data->cmds->args[0]);

	full_path = find_path(data->cmds->args[0], data->path_arr);
	printf("f path %s \n", full_path);

	return (EXIT_SUCCESS);
}