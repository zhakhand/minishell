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

void	set_word(t_token *tok, char *line, int *start, int *end)
{
	*end = *start;
	while (line[*end] != 32 && line[*end] != 0 && !is_sep(line[*end]))
		(*end)++;
	tok->val = ft_strndup(line + *start, *end - *start);
	*start = *end;
	tok->type = WORD;
}

void	handle_redir(t_token *tok, char *line, int *start, int *end)
{
	char	redir;
	int		len;

	redir = *(line + *start);
	*end = *start + 1;
	if (line[*end] == redir)
		(*end)++;
	len = *end - *start;
	tok->val = ft_strndup(line + *start, len);
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

void	handle_one(t_token *tok, char *line, int *start, int *end)
{
	if (line[*end] != '?' && (line[*end] == 32 || \
	line[*end] == 0 || line[*end] == '$' \
		|| !ft_isalnum(line[*end]) || line[*end] != '_'))
	{
		tok->val = ft_strndup(line + *start, *end - *start);
		tok->type = WORD;
	}
	else if (line[*end] == '?')
	{
		tok->val = ft_strndup(line + *start, ++(*end) - *start);
		tok->type = ERROR;
		tok->error = 1;
	}
	*start = *end;
}

void	handle_var(t_token *tok, char *line, int *start, int *end)
{
	*end = *start + 1;
	while (line[*end] != 32 && (ft_isalnum(line[*end]) \
	|| line[*end] == '_') && line[*end] != 0)
		(*end)++;
	if (*end - *start == 1)
		return (handle_one(tok, line, start, end));
	tok->val = ft_strndup(line + *start, *end - *start);
	tok->type = VAR;
	*start = *end;
}
