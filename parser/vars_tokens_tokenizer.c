/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_tokens_tokenizer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:08:06 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/27 14:02:20 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	fbi_open_up(t_token *new, t_data *data, int *start, int *end)
{
	*end = *start;
	while (data->line[*end] != 32 && data->line[*end] != 0 && data->line[*end] != '$')
		(*end)++;
	new->val = ft_strndup(data->line + *start, *end - *start, data);
	if (!new->val)
		end_it(data);
	*start = *end;
	new->type = WORD;
}

void	set_space_var(t_token *new, t_data *data, int *start, int *end)
{
	if (data->line[*start] == 32 || data->line[*start] == 9)
		return (set_space(new, data, start, end));
	else if (data->line[*start] == '$')
		return (handle_var(new, data, start, end));
}

t_token	*tokenize_quotes_vars(char *line, t_data *data)
{
	t_token	*head;
	t_token	*previous;
	t_token	*new;
	int		start;
	int		end;

	start = 0;
	end = 0;
	head = NULL;
	previous = NULL;
	data->line = line;
	while (data->line[start] && data->line[end])
	{
		new = init_token(data);
		if (!head)
			head = new;
		place_token(new, previous);
		if (data->line[start] == 32 || data->line[start] == '$')
			set_space_var(new, data, &start, &end);
		else
			fbi_open_up(new, data, &start, &end);
		previous = new;
	}
	data->line = NULL;
	return (head);
}
