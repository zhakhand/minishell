/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:55:49 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/21 16:00:40 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	error_msg(char *error, t_token *token, t_data *data)
{
	if (ft_strcmp(error, UNEXPECTED_TOKEN) == 0)
		ft_putstr_fd(error, 2);
	if (token == NULL)
		ft_putstr_fd("\'newline\'\n", 2);
	else
	{
		if (token->type == PIPE)
			ft_putstr_fd("\'|\'\n", 2);
		else if (token->type == IN)
			ft_putstr_fd("\'<\'\n", 2);
		else if (token->type == OUT)
			ft_putstr_fd("\'>\'\n", 2);
		else if (token->type == HEREDOC)
			ft_putstr_fd("\'<<\'\n", 2);
		else if (token->type == APPEND)
			ft_putstr_fd("\'>>\'\n", 2);
		else 
			ft_putstr_fd(token->val, 2);
	}
	if (ft_strcmp(error, CMD_NOT_FOUND) == 0)
		ft_putstr_fd(error, 2);
	data->err_no = 2;
	clean_data(data);
	exit(2);
}

