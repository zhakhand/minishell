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
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"

#define ES 98
#define WS 99
#define WORD 100
#define S_QUOTE 101
#define D_QUOTE 102
#define PIPE 103
#define IN 104
#define OUT 105
#define HEREDOC 106
#define APPEND 107
#define VAR 108
#define ERROR 109

#define ECH 901
#define CD   902
#define PWD  903
#define EXPORT 904
#define UNSET 905
#define ENV 906
#define EXIT 907

#define UNEXPECTED_TOKEN "syntax error near unexpected token "
#define CMD_NOT_FOUND ": command not found\n"

typedef struct s_var
{
	int	is_valid;
	char *key;
	char *val;
	struct s_var *next;
} t_var;

typedef struct s_token
{
	char *val;
	char *ogVal;
	int type;
	int was_quoted;
	struct s_token *next;
	struct s_token *prev;
} t_token;

typedef struct s_redir
{
	char *val;
	int type;
	struct s_redir	*next;
	struct s_redir	*prev;
} t_redir;

typedef struct s_cmd
{
	int	in;
	int	out;
	int abs_path;
	char 			*cmd;
	char 			**args;
	t_redir			*redir;
	int				built_in;
	struct s_cmd	*next;
	struct s_cmd	*prev;
} t_cmd;

typedef struct s_data
{
	int 	argc;
	int		err_no;
	char 	**args;
	char 	**path_arr;
	char	*path;
	char	*old_pwd;
	char	*pwd;
	t_var 	*user;
	t_var 	*env_var;
	t_token *tokens;
	t_cmd 	*cmds;
} t_data;

int is_sep(char c);
char *ft_strndup(char *str, int len);
int ft_strcmp(char *str1, char *str2);
int str_len(char *str);
char *ft_strjoin(char *s1, char *s2);
void	print_cmd_table(t_cmd *cmd);

//                     TOKENIZER                       //
t_token *tokenize(char *line);
t_token *tokenize_quotes_vars(char *line);
t_token *init_token(void);
void place_token(t_token *new, t_token *prev);
void set_token(t_token *tok, char *line, int *start, int *end);
void set_word(t_token *tok, char *line, int *start, int *end);
void set_space(t_token *tok, char *line, int *start, int *end);
void handle_quotes(t_token *tok, char *line, int *start, int *end);
void handle_redir(t_token *tok, char *line, int *start, int *end);
void handle_var(t_token *tok, char *line, int *start, int *end);

t_data *init_data(int ac, char **av, char **ev);
void copy_env(t_data *data, char **envp);
t_var *create_env_var(char *key, char *val);
t_var *get_env_var(t_data *data, char *key);
t_var *set_env_var(t_data *data, char *key, char *val);
void unset_var(t_data *data, char *key);
void reorder_tokens(t_data *data);
void merge_tokens(t_data *data);
void clear_out_es(t_data *data);
void delete_spaces(t_data *data);
void check_pipes(t_data *data);
void	check_redirs(t_data *data);
void	syntax_check(t_data *data);
t_token *relink_tokens(t_token *empty, t_token *current, t_data *data);

void	set_cmd_table(t_data *data);
int	is_redir(int type);
void	check_built_in(t_data *data);
void	error_msg(char *error, t_token *token, t_data *data);
void	free_tokens(t_token *token);
void	free_cmds(t_cmd *cmds);
void	clean_data(t_data *data);

#endif
