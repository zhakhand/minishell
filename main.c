/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:03:16 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/12/16 17:34:58 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	placeToken( t_token *new, t_token *prev)
{
	if (!prev)
		return;
	prev->next = new;
	new->prev = prev;
}

int	isSep(char c)
{
	if (c == '|' || c == '$' || c == '<' || c == '>' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

char	*strNDup(char *str, int len)
{
	char	*retStr;
	int		i;
	
	i = -1;
	retStr = malloc(sizeof(char *) * len + 1);
	if (!retStr)
		exit(2);
	while (++i < len)
		retStr[i] = str[i];
	retStr[i] = '\0';
	return (retStr);
}


void	setWord(t_token **tok, char *line, int *start, int *end)
{
	*end = *start;
	while (line[*end] != 32 && line[*end] != 0 && !isSep(line[*end]))
		(*end)++;
	(*tok)->val = strNDup(line + *start, *end - *start);
	*start = *end;
	(*tok)->type = WORD;
}

void	handleRedir(t_token **tok, char *line, int *start, int *end)
{
	char	*redir;
	int		len;

	redir = line + *start;
	*end = (*start)++;
	if (line[*end] == *redir)
		(*end)++;
	len = *end - *start;
	(*tok)->val = strNDup(line + *start, len);
	*start = *end;
	if (*redir == '<')
	{
		(*tok)->type = IN;
		if (len > 1)
			(*tok)->type = HEREDOC;
	}
	else if (*redir == '>')
	{
		(*tok)->type = OUT;
		if (len > 1)
			(*tok)->type = APPEND;
	}
}

void	handleVar(t_token **tok, char *line, int *start, int *end)
{
	*end = *start + 1;
	while (line[*end] != 32 && !isSep(line[*end]) && line[*end] != 0)
		(*end)++;
	(*tok)->val = strNDup(line + *start, *end - *start);
	(*tok)->type = VAR;
	*start = *end;
}

void	handleQuotation(t_token **tok, char *line, int *start, int *end)
{
	char *quote;
	
	quote = line + *start;
	(*start)++;
	*end = *start;
	while (line[*end] != *quote && line[*end] != 0)
		(*end)++;
	if (line[*end] == 0)
		exit(1);
	(*tok)->val = strNDup(line + *start, *start - *end);
	if (*quote == '\'')
		(*tok)->type = S_QUOTE;
	else
		(*tok)->type = D_QUOTE;
	*start = *end;
}

void	setToken(t_token **tok, char *line, int *start, int *end)
{
	if (line[*start] == '\'' || line[*start] == '\"')
		return handleQuotation(tok, line, start, end);
	if (line[*start] == '|')
	{
		(*tok)->val = strNDup(line + *start, 1);
		(*tok)->type = PIPE;
		(*start)++;
		*end = *start;
		return ;
	}
	if (line[*start] == '$')
		return handleVar(tok, line, start, end);
	if (line[*start] == '<' || line[*start] == '>')
		return handleRedir(tok, line, start, end);
}

t_token	*initToken(void)
{
	t_token	*new;
	
	new = malloc(sizeof(t_token));
	if (!new)
		exit(2);
	new->index = 0;
	new->next = NULL;
	new->prev = NULL;
	new->ogVal = NULL;
	new->type = 0;
	new->val = NULL;
	return (new);
}

t_token *tokenize(char *line)
{
	t_token *head;
	t_token *previous;
	t_token *new;
	int		start;
	int		end;
	
	start = 0;
	end = 0;
	head = NULL;
	previous = NULL;
	while (line[start] && line[end])
	{
		new = initToken();
		if(!head)
			head =new;
		if (line[start] == 32)
			start++;
		else
		{
			if (isSep(line[start]))
				setToken(&new, line, &start, &end);
			else
				setWord(&new, line, &start, &end);
			placeToken(new, previous);
			previous = new;
		}
	}
	return head;
}

int	main(int ac, char **av, char **ev)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmd;
	while (1)
	{
		line = readline("> ");
		tokens = tokenize(line);
		free(line);
		break;
	}
	while (tokens){
		printf("[%s] ", tokens->val);
		tokens = tokens->next;
	}
}