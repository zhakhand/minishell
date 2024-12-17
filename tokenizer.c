#include "parser.h"

void set_index(t_token *tok, char *line, int start)
{
	if (start != 0 && tok->prev && (line[start - 1] == 32 || is_sep(line[start - 1])))
    {
		tok->index = tok->prev->index + 1;
        return ;
    }
    else if (tok->prev)
    {
        tok->index = tok->prev->index;
    }
}

void	place_token( t_token *new, t_token *prev)
{
	if (!prev)
		return;
	prev->next = new;
	new->prev = prev;
}

void	set_word(t_token *tok, char *line, int *start, int *end)
{
    *end = *start;
    while (line[*end] != 32 && line[*end] != 0 && !is_sep(line[*end]))
        (*end)++;
    tok->val = ft_strndup(line + *start, *end - *start);
	//set_index(tok, line, *start);
    *start = *end;
    tok->type = WORD;
}

void	handle_redir(t_token *tok, char *line, int *start, int *end)
{
    char	redir;
    int		len;

    redir = *(line + *start);
	//printf("%c\n", redir);
    *end = *start + 1;
    if (line[*end] == redir)
        (*end)++;
    len = *end - *start;
    //printf("%d\n", len);
    tok->val = ft_strndup(line + *start, len);
	//set_index(tok, line, *start);
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

void	handle_var(t_token *tok, char *line, int *start, int *end)
{
    *end = *start + 1;
    while (line[*end] != 32 && !is_sep(line[*end]) && line[*end] != 0)
        (*end)++;
    tok->val = ft_strndup(line + *start, *end - *start);
    tok->type = VAR;
	//set_index(tok, line, *start);
    *start = *end;
}

void	handle_quotes(t_token *tok, char *line, int *start, int *end)
{
    char quote;

    quote = *(line + *start);
    //printf("%c\n", quote);
	//set_index(tok, line, *start);
    (*start)++;
    // if (line[*start] == 32)
    //     tok->index++;
    *end = *start;
    while (line[*end] != quote && line[*end] != '\0')
        (*end)++;
    if (line[*end] == '\0')
        exit(1);
    tok->val = ft_strndup(line + *start, *end - *start);
    if (quote == '\'')
        tok->type = S_QUOTE;
    else
        tok->type = D_QUOTE;
    *start = ++(*end);
}

void    set_space(t_token *tok, char *line, int *start, int *end)
{
    while (line[*start] == 32 && line[*start] != 0)
        (*start)++;
    *end = *start;
    tok->val = ft_strndup(" ", 1);
    tok->type = WS;
}

void	set_token(t_token *tok, char *line, int *start, int *end)
{
    if (line[*start] == 32)
        return set_space(tok, line, start, end);
    if (line[*start] == '\'' || line[*start] == '\"')
        return handle_quotes(tok, line, start, end);
    if (line[*start] == '|')
    {
        tok->val = ft_strndup(line + *start, 1);
		//set_index(tok, line, *start);
        tok->type = PIPE;
        (*start)++;
        *end = *start;
        return ;
    }
    if (line[*start] == '$')
        return handle_var(tok, line, start, end);
    if (line[*start] == '<' || line[*start] == '>')
        return handle_redir(tok, line, start, end);
}

t_token	*init_token(void)
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
        new = init_token();
        if(!head)
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
