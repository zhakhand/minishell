/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:34:25 by oshcheho          #+#    #+#             */
/*   Updated: 2025/02/19 13:34:25 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "parser.h"

typedef struct s_cmd_node
{
	struct s_redirects	*redirects;
	struct s_cmd_node	*left;
	struct s_cmd_node	*right;
	char				**cmd_args;
	int					cd;
	int					abs_path;
}						t_cmd_node;

typedef struct s_redirects
{
	struct s_redirects	*next;
	int					type;
	char				*file;
}			t_redirects;

void	clean_exit(t_data *data, int exit_code);

int		process_output_list(t_redir *temp, t_redir **out, t_redir **last_out);

void	run_child(t_data *data, t_cmd *cmd, char **envp, int prev_fd);

char	*get_i_for_cd_up(t_data *data);

int		add_to_env_end(char *str, t_data *data);
int		check_symbols(char *str);
int		add_to_env(char *str, t_data *data);
char	*add_quotes_to_val(char *str);
char	*add_quotes(char *str);
char	**sort_env(char **arr);
char	**make_env_arr(t_data *data);

void	s_e(t_data *data, int err_no);
int		init_parent_vars(t_data *data, t_cmd *cmd);
int		wait_last_pid(t_data *data, int count);

int		handle_input_redirects(t_redir *redir);
int		handle_output_redirects(t_redir *redirects);
int		process_input_list(t_redir *temp, t_redir **in, t_redir **last_input);
int		process_output_redirects(t_redir *output_redirects);
int		process_input_redirects(t_redir *input_redirects);
int		check_directory(char *file);

int		run_execve(t_data *data, t_cmd *cmd, char **envp);
int		get_random_fd(t_data *data);

int		exit_no_args(t_data *data, t_cmd *node);

char	*get_temp_name(int pid);

void	free_node(t_cmd_node *node);
void	free_node_2(t_cmd_node *node);

void	ft_putmsg_fd(char *msg1, char *msg2, char *msg3, int fd);
int		ft_edge_cases(t_data *data, t_cmd *cmd);

int		exec_buildin(t_data *data, t_cmd *node);
int		handle_redirects(t_data *data, t_cmd *node);

int		get_old_pwd(t_data *data);
int		change_pwd_in_env(t_data *data, char *pwd);
int		change_old_pwd_in_env(t_data *data, char *pwd);
char	*get_home(t_data *data);
void	check_abs_path(t_cmd *node);

int		ft_env_no_args(t_data *data);
int		ft_echo(t_data *data, t_cmd *node);
int		ft_export(t_data *data, t_cmd *node);
int		changedir(t_data *data, t_cmd *node);
int		ft_exit(t_data *data, t_cmd *node);

void	ft_unset(t_data *data, t_cmd *node);
char	**sort_env(char **arr);
char	*get_pwd(t_data *data);

void	free_array(char ***arr);
void	free_data(t_data *data);

int		check_parent_buildin(t_cmd *node);
int		check_child_buildin(t_cmd *node);
int		show_pwd(t_data *data);

void	panic(char *msg);
void	find_env_in_cmd(t_cmd_node **node, t_data *data);
int		get_arr_lines(char **arr);
void	get_envs(t_data *data, char **envp);
int		run_pipe(t_data *data, t_cmd *cmd, char **envp);
char	*find_path(char *cmd, char **envp);
char	**get_path_arr(char **envp);
void	print_path(char **path_arr);
void	run(t_cmd_node *list, char **envp);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s);

#endif