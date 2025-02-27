/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:59:35 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/27 14:00:01 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	free_args(char ***args)
{
	int	i;

	i = 0;
	if (!args || !*args)
		return ;
	while ((*args)[i] != NULL)
	{
		free((*args)[i]);
		(*args)[i] = NULL;
		i++;
	}
	free(*args);
	*args = NULL;
}

void	free_redirs(t_redir *redir)
{
	t_redir	*curr;
	t_redir	*to_free;

	curr = redir;
	to_free = NULL;
	while (curr)
	{
		to_free = curr;
		curr = curr->next;
		if (to_free->heredoc)
		{
			unlink(to_free->heredoc);
			free(to_free->heredoc);
			to_free->heredoc = NULL;
		}
		if (to_free->val)
			free(to_free->val);
		to_free->val = NULL;
		free(to_free);
		to_free = NULL;
	}
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*curr;
	t_cmd	*to_free;

	curr = cmd;
	to_free = NULL;
	while (curr)
	{
		to_free = curr;
		curr = curr->next;
		if (to_free->args)
			free_args(&to_free->args);
		to_free->args = NULL;
		to_free->cmd = NULL;
		if (to_free->redir)
			free_redirs(to_free->redir);
		to_free->redir = NULL;
		if (to_free)
			free(to_free);
		to_free = NULL;
	}
}
