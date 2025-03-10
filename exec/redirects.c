/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:19:58 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 12:19:58 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_directory(char *file, t_data *data)
{
	struct stat	sb;
	char		*temp;
	int			i;

	i = ft_strlen(file);
	while (i > 0)
	{
		if (file[i] == '/')
			break ;
		i--;
	}
	if (i == 0)
		temp = ft_strdup(file);
	else
		temp = ft_substr(file, 0, i);
	if (!temp)
		return (-1);
	if (stat(temp, &sb) != 0 && i != 0)
		return (ft_putmsg_fd(MSH, file, N_F_D, data), free(temp), -1);
	if (stat(file, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (ft_putmsg_fd(MSH, file, I_A_D, data), free(temp), -1);
	free(temp);
	if (open_out(file, data) == -1)
		return (-1);
	return (0);
}

int	check_access(char *file, t_data *data)
{
	if (access(file, F_OK) == -1)
	{
		ft_putmsg_fd(MSH, file, N_F_D, data);
		return (-1);
	}
	return (0);
}

int	check_redirect(t_redir *redir, t_data *data)
{
	if (redir->type == IN && check_access(redir->val, data) == -1)
		return (-1);
	else if ((redir->type == OUT || redir->type == APPEND)
		&& check_directory(redir->val, data) == -1)
		return (-1);
	return (0);
}

int	process_redir_list(t_redir *temp, t_data *data)
{
	while (temp)
	{
		if (check_redirect(temp, data) == -1)
			return (-1);
		temp = temp->next;
	}
	return (0);
}

int	handle_redirects(t_data *data, t_cmd *node)
{
	int		err;

	err = 0;
	if (process_redir_list(node->redirs, data) == -1)
		return (-1);
	if (process_input_redirects(node->redir_in, data) == -1)
		return (-1);
	if (process_output_redirects(node->redir_out, data) == -1)
		return (-1);
	data->err_no = err;
	return (err);
}
