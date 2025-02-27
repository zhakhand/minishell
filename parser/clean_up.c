/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:11:46 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/27 14:00:40 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	free_tokens(t_token *token)
{
	t_token	*curr;
	t_token	*to_free;

	curr = NULL;
	if (token)
		curr = token;
	to_free = NULL;
	while (curr)
	{
		to_free = curr;
		curr = curr->next;
		if (to_free->val)
			free(to_free->val);
		to_free->val = NULL;
		if (to_free->ogval)
			free(to_free->ogval);
		to_free->ogval = NULL;
		if (to_free)
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

void	clean_data_helper(t_data *data)
{
	if (data->tokens)
		free_tokens(data->tokens);
	if (data->cmds)
		free_cmds(data->cmds);
	if (data->path_arr)
		free_args(&data->path_arr);
	if (data->env)
		free_args(&data->env);
	data->tokens = NULL;
	data->cmds = NULL;
	if (data->env_var)
		clean_env(data);
	if (data->old_pwd)
		free(data->old_pwd);
	if (data->pwd)
		free(data->pwd);
	if (data->path)
		free(data->path);
	if (data->temp_name)
		free(data->temp_name);
	free(data->line);
}

void	clean_data(t_data *data)
{
	if (!data)
		return ;
	clean_data_helper(data);
	free(data);
	data = NULL;
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void	reset_data(t_data *data)
{
	free(data->line);
	data->line = NULL;
	if (!data)
		return ;
	if (data->tokens)
		free_tokens(data->tokens);
	if (data->cmds)
		free_cmds(data->cmds);
	if (data->path_arr)
		free_args(&data->path_arr);
	if (data->env)
		free_args(&data->env);
	if (data->temp_name)
		free(data->temp_name);
	data->temp_name = NULL;
	data->path_arr = NULL;
	data->tokens = NULL;
	data->cmds = NULL;
	data->we_have_child = 0;
}
