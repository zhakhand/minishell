/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:18:50 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/27 12:53:19 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	place_token(t_token *new, t_token *prev)
{
	if (!prev)
		return ;
	prev->next = new;
	new->prev = prev;
}

void	set_word(t_token *tok, t_data *data, int *start, int *end)
{
	*end = *start;
	while (data->line[*end] != 32 && data->line[*end] != 0 \
	&& !is_sep(data->line[*end]))
		(*end)++;
	tok->val = ft_strndup(data->line + *start, *end - *start, data);
	if (!tok->val)
		end_it(data);
	*start = *end;
	tok->type = WORD;
}

void	handle_redir(t_token *tok, t_data *data, int *start, int *end)
{
	char	redir;
	int		len;

	redir = *(data->line + *start);
	*end = *start + 1;
	if (data->line[*end] == redir)
		(*end)++;
	len = *end - *start;
	tok->val = ft_strndup(data->line + *start, len, data);
	if (!tok->val)
		end_it(data);
	*start = *end;
	if (redir == '<')
	{
		tok->type = IN;
		if (len > 1)
			tok->type = HEREDOC;
	}
	else if (redir == '>')
	{
		tok->type = OUT;
		if (len > 1)
			tok->type = APPEND;
	}
}

void	handle_one(t_token *tok, t_data *data, int *start, int *end)
{
	if (data->line[*end] != '?' && (data->line[*end] == 32 \
	|| data->line[*end] == 0 || data->line[*end] == '$' \
		|| !ft_isalnum(data->line[*end]) || data->line[*end] != '_'))
	{
		tok->val = ft_strndup(data->line + *start, *end - *start, data);
		if (!tok->val)
			end_it(data);
		tok->type = WORD;
	}
	else if (data->line[*end] == '?')
	{
		tok->val = ft_strndup(data->line + *start, ++(*end) - *start, data);
		if (!tok->val)
			end_it(data);
		tok->type = ERROR;
		tok->error = 1;
	}
	*start = *end;
}

void	handle_var(t_token *tok, t_data *data, int *start, int *end)
{
	*end = *start + 1;
	while (data->line[*end] != 32 && (ft_isalnum(data->line[*end]) \
	|| data->line[*end] == '_') && data->line[*end] != 0)
		(*end)++;
	if (*end - *start == 1)
		return (handle_one(tok, data, start, end));
	tok->val = ft_strndup(data->line + *start, *end - *start, data);
	if (!tok->val)
		end_it(data);
	tok->type = VAR;
	*start = *end;
}
