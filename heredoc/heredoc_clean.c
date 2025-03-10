/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:32:46 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/02/01 17:35:35 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parser.h"

void	end_it(t_data *data)
{
	clean_data(data);
	panic("malloc");
}

void	heredoc_msg(t_redir *redir)
{
	ft_putstr_fd(H_D_D, STDERR_FILENO);
	ft_putstr_fd(redir->val, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}
