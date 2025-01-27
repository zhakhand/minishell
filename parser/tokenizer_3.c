/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:01 by dzhakhan          #+#    #+#             */
/*   Updated: 2025/01/27 15:29:16 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include "../minishell.h"

int	handle_quotes(t_token *tok, char *line, int *start, int *end)
{
	char	quote;

	quote = *(line + *start);
	(*start)++;
	*end = *start;
	while (line[*end] != quote && line[*end] != '\0')
		(*end)++;
	if (line[*end] == '\0')
		return (ft_putstr_fd("syntax error: unclosed quotes!\n", 2), 0);
	if (*end - *start == 0)
	{
		tok->type = WORD;
		tok->val = ft_strdup("");
		tok->was_quoted = 1;
		*start = ++(*end);
		return (1);
	}
	tok->val = ft_strndup(line + *start, *end - *start);
	if (quote == '\'')
		tok->type = S_QUOTE;
	else
		tok->type = D_QUOTE;
	*start = ++(*end);
	return (1);
}
