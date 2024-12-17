/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:54:28 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/12/16 17:00:40 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WORD 100
# define S_QUOTE 101
# define D_QUOTE 102
# define PIPE 103
# define IN 104
# define OUT 105
# define HEREDOC 106
# define APPEND 107
# define VAR 108

typedef struct s_var
{
	char			*key;
	char			*val;
	struct s_var	*next;
}				t_var;

typedef struct s_token 
{
	char	*val;
	char	*ogVal;
	int		index;
	int		type;
	struct s_token *next;
	struct s_token *prev;
}				t_token;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	**redirs;
	struct s_cmd *next;
	struct s_cmd *prev;
}				t_cmd;

typedef struct s_data
{
	int		argc;
	char	**args;
	t_var	*user;
	t_var	*envVar;
	t_token	*tokens;
	t_cmd	*cmds;	
}				t_data;

t_token *tokenize(char *line);
int		isSep(char c);
char	*strNDup(char *str, int len);
int		strCmp(char *str1, char *str2);
int		strLen(char *str);

//                     TOKENIZER                                    //
void 	placeToken(t_token *new, t_token *prev);
void 	setToken(t_token *tok, char *line, int *start, int *end);
void 	setWord(t_token *tok, char *line, int *start, int *end);
void 	handleQuotation(t_token *tok, char *line, int *start, int *end);
void 	handleRedir(t_token *tok, char *line, int *start, int *end);
void 	handleVar(t_token *tok, char *line, int *start, int *end);

t_data *initData(int ac, char **av, char **ev);
void	copyEnv(t_data *data, char **envp);
t_var	*createEnvVar(char *key, char *val);
char	*userName(t_data *data);
t_var	*getEnvVar(t_data *data, char *key);
void	setEnvVar(t_data *data, char *key, char *val);
void	unsetVar(t_data *data, char *key);

#endif