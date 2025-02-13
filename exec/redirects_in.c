/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:19:45 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/13 12:19:45 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_in(t_redir *redir)
{
	int	in_fd;

	if (redir->ambig == 1)
	{
		ft_putmsg_fd(MSH, redir->val, AMB, STDERR_FILENO);
		return (-1);
	}
	in_fd = open(redir->val, O_RDONLY);
	if (in_fd == -1)
	{
		ft_putmsg_fd(MSH, redir->val, N_F_D, STDERR_FILENO);
		return (-1);
	}
	if (dup2(in_fd, STDIN_FILENO) == -1)
		return (-1);
	close(in_fd);
	return (0);
}

int	handle_input_redirects(t_redir *redir)
{
	t_redir	*redirects;
	int		in_fd;

	redirects = redir;
	while (redirects)
	{
		if (redirects->type == IN)
		{
			if (handle_in(redirects) == -1)
				return (-1);
		}
		else if (redirects->type == HEREDOC)
		{
			set_signals(HEREDOC);
			in_fd = open(redirects->heredoc, O_RDONLY);
			if (in_fd == -1)
				return (ft_putmsg_fd(MSH, redirects->heredoc, N_F_D, 2), -1);
			if (dup2(in_fd, STDIN_FILENO) == -1)
				return (-1);
			close(in_fd);
		}
		redirects = redirects->next;
	}
	return (0);
}
