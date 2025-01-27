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

void	fbi_open_up(t_token *new, char *line, int *start, int *end)
{
	*end = *start;
	while (line[*end] != 32 && line[*end] != 0 && line[*end] != '$')
		(*end)++;
	new->val = ft_strndup(line + *start, *end - *start);
	*start = *end;
	new->type = WORD;
}

void	set_space_var(t_token *new, char *line, int *start, int *end)
{
	if (line[*start] == 32)
		return (set_space(new, line, start, end));
	else if (line[*start] == '$')
		return (handle_var(new, line, start, end));
}

t_token	*tokenize_quotes_vars(char *line)
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
	while (line[start] && line[end])
	{
		new = init_token();
		if (!head)
			head = new;
		place_token(new, previous);
		if (line[start] == 32 || line[start] == '$')
			set_space_var(new, line, &start, &end);
		else
			fbi_open_up(new, line, &start, &end);
		previous = new;
	}
	return (head);
}
