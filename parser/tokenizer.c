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

void	set_space(t_token *tok, char *line, int *start, int *end)
{
	*end = *start;
	while ((line[*end] == 32 || line[*end] == 9) && line[*end] != 0)
		(*end)++;
	tok->val = ft_strndup(line + *start, *end - *start);
	*start = *end;
	tok->type = WS;
}

int	set_token(t_token *tok, char *line, int *start, int *end)
{
	if (line[*start] == 32 || line[*start] == 9)
		return (set_space(tok, line, start, end), 1);
	if (line[*start] == '\'' || line[*start] == '\"')
		return (handle_quotes(tok, line, start, end));
	if (line[*start] == '|')
	{
		tok->val = ft_strndup(line + *start, 1);
		tok->type = PIPE;
		(*start)++;
		*end = *start;
		return (1);
	}
	if (line[*start] == '$')
		return (handle_var(tok, line, start, end), 1);
	if (line[*start] == '<' || line[*start] == '>')
		return (handle_redir(tok, line, start, end), 1);
	return (1);
}

t_token	*init_token(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		panic("malloc");
	new->was_quoted = 0;
	new->is_ambiguous = 0;
	new->touches_next = 0;
	new->error = 0;
	new->is_delim = 0;
	new->next = NULL;
	new->prev = NULL;
	new->ogVal = NULL;
	new->type = 0;
	new->val = NULL;
	return (new);
}

int	handle_tokens(t_token *new, char *line, int *start, int *end)
{
	if (is_sep(line[*start]))
	{
		if (set_token(new, line, start, end) == 0)
			return (0);
	}
	else
		set_word(new, line, start, end);
	return (1);
}

t_token	*tokenize(char *line)
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
		if (handle_tokens(new, line, &start, &end) == 0)
			return (free_tokens(head), NULL);
		previous = new;
	}
	return (head);
}
