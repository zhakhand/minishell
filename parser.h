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
# include "./libft/libft.h"

# define ES 98
# define WS 99
# define WORD 100
# define S_QUOTE 101
# define D_QUOTE 102
# define PIPE 103
# define IN 104
# define OUT 105
# define HEREDOC 106
# define APPEND 107
# define VAR 108
# define ERROR 109

# define ECH 901
# define CD   902
# define PWD  903
# define EXPORT 904
# define UNSET 905
# define ENV 906
# define EXIT 907

# define PARENT 40001
# define CHILD 40002
# define WAIT 40003

# define UNEXPECTED_TOKEN "syntax error near unexpected token "
# define CMD_NOT_FOUND ": command not found\n"
# define MSH "minishell: "
# define EX "exit: "
# define MSH_CD "minishell: cd: "
# define AMB ": ambiguous redirect\n"
# define NAR ": numeric argument required\n"
# define NVI "': not a valid identifier\n"
# define P_D ": Permission denied\n"
# define T_M_A ": too many arguments\n"
# define E_T_M_A "exit: too many arguments\n"
# define C_N_F ": command not found\n"
# define I_A_D ": Is a directory\n"
# define N_A_D ": Not a directory\n"
# define N_F_D ": No such file or directory\n"
# define F_C_D ": Failed to change directory\n"
# define H_D_D "minishell: warning: heredoc delimited by EOF (wanted `"
# define O_PWD "OLDPWD not set"

typedef struct s_var
{
	int				is_valid;
	char			*key;
	char			*val;
	struct s_var	*next;
}	t_var;

typedef struct s_token
{
	char			*val;
	char			*ogval;
	int				type;
	int				is_ambiguous;
	int				was_quoted;
	int				touches_next;
	int				is_delim;
	int				error;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_redir
{
	char			*val;
	char			*heredoc;
	int				type;
	int				expands;
	int				ambig;
	int				fd;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef struct s_cmd
{
	int				in;
	int				out;
	int				fds[2];
	int				abs_path;
	int				args_count;
	char			*cmd;
	char			**args;
	t_redir			*redir_in;
	t_redir			*redir_out;
	t_redir			*redirs;
	int				built_in;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_data
{
	int		prev_fd;
	int		argc;
	int		err_no;
	int		last_err;
	int		last_pid;
	int		redir_err;
	int		child_start;
	int		we_have_child;
	int		out_fd;
	char	*temp_name;
	char	*line;
	char	*full_path;
	char	**args;
	char	**env;
	char	**path_arr;
	char	*path;
	char	*old_pwd;
	char	*pwd;
	t_var	*env_var;
	t_token	*tokens;
	t_cmd	*cmds;
	int		pid[1024];
}	t_data;

char	*ft_strndup(char *str, int len, t_data *data);
char	*ft_strjoin(char *s1, char *s2);
void	print_cmd_table(t_cmd *cmd);
int		is_sep(char c);
int		ft_strcmp(char *str1, char *str2);
int		str_len(char *str);

//                     PARSER                       //
t_token	*tokenize(t_data *data);
t_token	*tokenize_quotes_vars(char *line, t_data *data);
t_token	*init_token(t_data *data);
void	place_token(t_token *new, t_token *prev);
void	set_word(t_token *tok, t_data *data, int *start, int *end);
void	set_space(t_token *tok, t_data *data, int *start, int *end);
void	handle_redir(t_token *tok, t_data *data, int *start, int *end);
void	handle_var(t_token *tok, t_data *data, int *start, int *end);
int		handle_quotes(t_token *tok, t_data *data, int *start, int *end);
int		set_token(t_token *tok, t_data *data, int *start, int *end);
t_token	*link_tokens(t_token *token, t_token *head, t_token *tail);
t_token	*relink_tokens(t_token *empty, t_token *current, t_data *data);
void	clear_quote_tokens(t_data *data);
void	expand_vars(t_data *data);
void	mark_merges(t_token *tokens);
void	merge_tokens(t_data *data);
void	clear_out_es(t_data *data);
void	delete_spaces(t_data *data);
int		reorder_tokens(t_data *data);
t_token	*count_args(int *count, t_token *token);
t_token	*put_cmds(t_token *token, t_cmd *cmd, t_data *data);
t_redir	*init_redir(t_data *data);
void	add_to_list(t_token *token, t_redir *tail);
void	add_to_list_no_del(t_token *token, t_redir *tail, t_data *data);
t_redir	*redir_list_in(t_token *token, t_data *data);
t_redir	*redir_list_out(t_token *token, t_data *data);
void	set_cmd_table(t_data *data);
void	fill_args(t_cmd *cmd, t_token *token);
void	check_built_in(t_data *data);
int		is_redir(int type);
int		error_msg(char *error, t_token *token, t_data *data);

//						DATA / ENV					//
t_data	*init_data(int ac, char **av, char **ev);
t_var	*push_back(t_data *data, t_var *new);
t_var	*create_env_var(char *key, char *val, t_data *data);
t_var	*get_env_var(t_data *data, char *key);
t_var	*set_env_var(t_data *data, char *key, char *val);
void	copy_env(t_data *data, char **envp);
void	increase_shell_lvl(t_data *data);
void	unset_var(t_data *data, char *key);

//					SYNTAX					//
int		check_pipes(t_data *data);
int		pipe_check(t_data *data, t_token *current);
int		check_redirs(t_data *data);

//						CLEAN UP				//
void	free_and_null(char **str);
void	free_tokens(t_token *token);
void	free_cmds(t_cmd *cmds);
void	free_args(char	***args);
void	clean_data(t_data *data);
void	reset_data(t_data *data);
void	end_it(t_data *data);

//						SIGNALS					//
void	set_signals(int mode);

//						HEREDOC					//
char	*expand_heredoc(char *line, t_data *data);
void	add_to_line(char c, char **line, t_data *data);
int		heredoc(t_data *data);
void	heredoc_msg(t_redir *redir);

#endif
