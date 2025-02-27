/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:19:50 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 12:19:50 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_and_close(t_redir *redir, t_data *data)
{
	int	out_fd;

	out_fd = -1;
	if (ft_strcmp(redir->val, "/dev/null") == 0)
		return (0);
	out_fd = open(redir->val, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (out_fd == -1)
		return (ft_putmsg_fd(MSH, redir->val, N_F_D, data), -1);
	close(out_fd);
	return (0);
}

int	handle_out_helper(t_redir *redir, t_data *data)
{
	int	out_fd;

	out_fd = -1;
	if (redir->type == OUT)
		out_fd = open(redir->val, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (redir->type == APPEND)
		out_fd = open(redir->val, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (out_fd == -1)
	{
		ft_putmsg_fd(MSH, redir->val, N_F_D, data);
		return (-1);
	}
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		return (-1);
	close(out_fd);
	return (0);
}

int	handle_output_redirects(t_redir *redirects, t_data *data)
{
	t_redir	*redir;

	redir = redirects;
	if (check_directory(redirects->val, data) == -1)
		return (-1);
	while (redir)
	{
		if (redirects->ambig == 1)
			return (ft_putmsg_fd(MSH, redirects->val, AMB, data), -1);
		if (redir->next)
		{
			if (open_and_close(redir, data))
				return (-1);
		}
		else
		{
			if (handle_out_helper(redir, data) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}
