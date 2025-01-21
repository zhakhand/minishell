#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parser.h"


typedef struct s_cmd_node
{
	char **cmd_args;
	// char *in_file;
	// char *out_file;
	// char *out_heredoc;
	// char *in_heredoc;
	struct s_redirects *redirects;
	int cd;
	int abs_path;
	struct s_cmd_node *left;
	struct s_cmd_node *right;
}			t_cmd_node;


typedef struct s_redirects
{
	int		type;
	char	*file;
	struct s_redirects *next;
}			t_redirects;

// typedef struct s_data
// {
// 	char	**path_arr;
// 	char 	**env;
// //	char 	**pwd;

// }			t_data;




void free_node(t_cmd_node *node);
void free_node_2(t_cmd_node *node);

int exec_buildin(t_data *data, t_cmd *node);
int handle_redirects(t_cmd *node);

int ft_env_no_args(t_data *data);
char **sort_env(char **arr);
int ft_echo(t_data *data, t_cmd *node);
int ft_unset(t_data *data, t_cmd *node);
int ft_export(t_data *data, t_cmd *node);
int changedir(t_data *data, t_cmd *node);
char *get_pwd(t_data *data);
int ft_exit(t_data *data, t_cmd *node);


void free_array(char ***arr);
void free_data(t_data *data);
int check_if_buildin(t_cmd *node);
int show_pwd(t_data *data);
void panic(char *msg);
void find_env_in_cmd(t_cmd_node **node, t_data *data);
int get_arr_lines(char **arr);
void get_envs(t_data *data, char **envp);
int run_pipe(t_data *data, t_cmd *cmd, char **envp);
void run_fork(t_cmd_node *list, char **envp);
char *find_path(char *cmd, char **envp);
char **get_path_arr(char **envp);
void print_path(char **path_arr);
void 	run(t_cmd_node *list, char **envp);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s);

int execute(t_data *data, char **envp);


#endif