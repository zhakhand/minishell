#include "parser.h"

void setIndex(t_token *tok, char *line, int start)
{
	if (start != 0 && line[start - 1] == 32 && tok->prev)
		tok->index = tok->prev->index + 1;
	else if (tok->prev)
		tok->index = tok->prev->index;
}

void	placeToken( t_token *new, t_token *prev)
{
	if (!prev)
		return;
	prev->next = new;
	new->prev = prev;
}

void	setWord(t_token *tok, char *line, int *start, int *end)
{
    *end = *start;
    while (line[*end] != 32 && line[*end] != 0 && !isSep(line[*end]))
        (*end)++;
    tok->val = strNDup(line + *start, *end - *start);
	setIndex(tok, line, *start);
    *start = *end;
    tok->type = WORD;
}

void	handleRedir(t_token *tok, char *line, int *start, int *end)
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
    tok->val = strNDup(line + *start, len);
	setIndex(tok, line, *start);
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

void	handleVar(t_token *tok, char *line, int *start, int *end)
{
    *end = *start + 1;
    while (line[*end] != 32 && !isSep(line[*end]) && line[*end] != 0)
        (*end)++;
    tok->val = strNDup(line + *start, *end - *start);
    tok->type = VAR;
	setIndex(tok, line, *start);
    *start = *end;
}

void	handleQuotation(t_token *tok, char *line, int *start, int *end)
{
    char quote;

    quote = *(line + *start);
    //printf("%c\n", quote);
	setIndex(tok, line, *start);
    (*start)++;
    *end = *start;
    //printf("%c\n", line[*end]);
    while (line[*end] != quote && line[*end] != '\0')
        (*end)++;
	//printf("%d\n", *end - *start);
	//printf("%c\n", line[*end]);
    if (line[*end] == '\0')
        exit(1);
    tok->val = strNDup(line + *start, *end - *start);
	printf("%s\n", tok->val);
    if (quote == '\'')
        tok->type = S_QUOTE;
    else
        tok->type = D_QUOTE;
    *start = ++(*end);
}

void	setToken(t_token *tok, char *line, int *start, int *end)
{
    if (line[*start] == '\'' || line[*start] == '\"')
        return handleQuotation(tok, line, start, end);
    if (line[*start] == '|')
    {
        tok->val = strNDup(line + *start, 1);
		setIndex(tok, line, *start);
        tok->type = PIPE;
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
            placeToken(new, previous);
            if (isSep(line[start]))
                setToken(new, line, &start, &end);
            else
                setWord(new, line, &start, &end);
            previous = new;
        }
    }
    return head;
}
