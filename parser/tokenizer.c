/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:40:46 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/12/19 12:40:46 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include "../minishell.h"

void	set_space(t_token *tok, t_data *data, int *start, int *end)
{
	*end = *start;
	while ((data->line[*end] == 32 || data->line[*end] == 9) \
	&& data->line[*end] != 0)
		(*end)++;
	tok->val = ft_strndup(data->line + *start, *end - *start, data);
	if (!tok->val)
		end_it(data);
	*start = *end;
	tok->type = WS;
}

int	set_token(t_token *tok, t_data *data, int *start, int *end)
{
	if (data->line[*start] == 32 || data->line[*start] == 9)
		return (set_space(tok, data, start, end), 1);
	if (data->line[*start] == '\'' || data->line[*start] == '\"')
		return (handle_quotes(tok, data, start, end));
	if (data->line[*start] == '|')
	{
		tok->val = ft_strndup(data->line + *start, 1, data);
		if (!tok->val)
			end_it(data);
		tok->type = PIPE;
		(*start)++;
		*end = *start;
		return (1);
	}
	if (data->line[*start] == '$')
		return (handle_var(tok, data, start, end), 1);
	if (data->line[*start] == '<' || data->line[*start] == '>')
		return (handle_redir(tok, data, start, end), 1);
	return (1);
}

t_token	*init_token(t_data *data)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		end_it(data);
	new->was_quoted = 0;
	new->is_ambiguous = 0;
	new->touches_next = 0;
	new->error = 0;
	new->is_delim = 0;
	new->next = NULL;
	new->prev = NULL;
	new->ogval = NULL;
	new->type = 0;
	new->val = NULL;
	return (new);
}

int	handle_tokens(t_token *new, t_data *data, int *start, int *end)
{
	if (is_sep(data->line[*start]))
	{
		if (set_token(new, data, start, end) == 0)
			return (0);
	}
	else
		set_word(new, data, start, end);
	return (1);
}

t_token	*tokenize(t_data *data)
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
	while (data->line[start] && data->line[end])
	{
		new = init_token(data);
		if (!head)
			head = new;
		place_token(new, previous);
		if (handle_tokens(new, data, &start, &end) == 0)
			return (free_tokens(head), NULL);
		previous = new;
	}
	return (head);
}
