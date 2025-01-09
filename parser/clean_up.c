/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:11:46 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/09 19:46:26 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	free_args(char	**args)
{
	int	i;

	i = 0;
	while (args[i] != 0)
	{
		free(args[i]);
		args[i] = NULL;
	}
	free(args);
	args = NULL;
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
			free_args(to_free->args);
		to_free->args = NULL;
		to_free->cmd = NULL;
		if (to_free->redir)
			free_redirs(to_free->redir);
		to_free->redir = NULL;
		free(to_free);
		to_free = NULL;
	}
}

void	free_tokens(t_token *token)
{
	t_token	*curr;
	t_token	*to_free;

	curr = token;
	to_free = NULL;
	while (curr)
	{
		to_free = curr;
		curr = curr->next;
		if (to_free->val)
			free(to_free->val);
		to_free->val = NULL;
		if (to_free->ogVal)
			free(to_free->ogVal);
		to_free->ogVal = NULL;
		free(to_free);
		to_free = NULL;
	}
}

void	clean_env(t_data *data)
{
	t_var	*curr;
	t_var	*to_free;

	curr = data->env_var;
	to_free = NULL;
	while (curr)
	{
		to_free = curr;
		curr = curr->next;
		if (to_free->key)
			free(to_free->key);
		to_free->key = NULL;
		if (to_free->val)
			free(to_free->val);
		to_free->val = NULL;
		free(to_free);
		to_free = NULL;
	}
}

void	clean_data(t_data *data)
{
	if (!data)
		return ;
	if (data->tokens)
		free_tokens(data->tokens);
	if (data->cmds)
		free_cmds(data->cmds);
	data->tokens = NULL;
	data->cmds = NULL;
	if (data->env_var)
		clean_env(data);
	if (data->old_pwd)
		free(data->old_pwd);
	if (data->path)
		free(data->path);
	free(data);
	data = NULL;	
}
