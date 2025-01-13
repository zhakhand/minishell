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

void place_token(t_token *new, t_token *prev)
{
    if (!prev)
        return;
    prev->next = new;
    new->prev = prev;
}

void set_word(t_token *tok, char *line, int *start, int *end)
{
    *end = *start;
    while (line[*end] != 32 && line[*end] != 0 && !is_sep(line[*end]))
        (*end)++;
    tok->val = ft_strndup(line + *start, *end - *start);
    *start = *end;
    tok->type = WORD;
}

void handle_redir(t_token *tok, char *line, int *start, int *end)
{
    char redir;
    int len;

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

void handle_var(t_token *tok, char *line, int *start, int *end)
{
    *end = *start + 1;
    while (line[*end] != 32 && line[*end] != '?' && !is_sep(line[*end]) && line[*end] != 0)
        (*end)++;
    if (*end - *start == 1)
    {
        if (line[*end] == 32 || line[*end] == 0 || line[*end] == '$')
        {
            tok->val = ft_strndup(line + *start, *end - *start);
            tok->type = WORD;
        }
        else if (line[*end] == '?')
        {
            tok->val = ft_strndup(line + *start, ++(*end) - *start);
            tok->type = ERROR;
        }
        *start = *end;
//        printf("%s\n", tok->val); 
        return ;
    }
    tok->val = ft_strndup(line + *start, *end - *start);
    tok->type = VAR;
    *start = *end;
}

void handle_quotes(t_token *tok, char *line, int *start, int *end)
{
    char quote;

    quote = *(line + *start);
    (*start)++;
    *end = *start;
    while (line[*end] != quote && line[*end] != '\0')
        (*end)++;
    if (line[*end] == '\0')
        exit(1);
    if (*end - *start == 0)
    {
        tok->type = ES;
        tok->val = ft_strdup("");
        tok->was_quoted = 1;
        *start = ++(*end);
        return;
    }
    tok->val = ft_strndup(line + *start, *end - *start);
    if (quote == '\'')
        tok->type = S_QUOTE;
    else
        tok->type = D_QUOTE;
    *start = ++(*end);
}

void set_space(t_token *tok, char *line, int *start, int *end)
{
    *end = *start;
    while (line[*end] == 32 && line[*end] != 0)
        (*end)++;
    tok->val = ft_strndup(line + *start, *end - *start);
    *start = *end;
    tok->type = WS;
}

void set_token(t_token *tok, char *line, int *start, int *end)
{
    if (line[*start] == 32)
        return set_space(tok, line, start, end);
    if (line[*start] == '\'' || line[*start] == '\"')
        return handle_quotes(tok, line, start, end);
    if (line[*start] == '|')
    {
        tok->val = ft_strndup(line + *start, 1);
        tok->type = PIPE;
        (*start)++;
        *end = *start;
        return;
    }
    if (line[*start] == '$')
        return handle_var(tok, line, start, end);
    if (line[*start] == '<' || line[*start] == '>')
        return handle_redir(tok, line, start, end);
}

t_token *init_token(void)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if (!new)
        exit(2);
    new->was_quoted = 0;
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
    int start;
    int end;

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
        if (is_sep(line[start]))
            set_token(new, line, &start, &end);
        else
            set_word(new, line, &start, &end);
        previous = new;
    }
    return head;
}
