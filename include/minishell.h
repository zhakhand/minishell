/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:15:56 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/12/13 14:52:23 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>			   //printf, perror
#include <readline/readline.h> //readline, add_history
#include <readline/history.h>  //rl_clear_history
#include <stdlib.h>			   //malloc, free, exit, getenv
#include <unistd.h>			   //close, read, write, fork, execve, chdir, getcwd
#include <string.h>			   //strerror
#include <signal.h>			   //signal, sigaction
#include <fcntl.h>			   //open
#include <sys/types.h>		   //data types and functions
#include <sys/stat.h>		   // stat, fstat
#include <dirent.h>			   //oopendir, readdir, closedir
#include <termios.h>		   //tcgetattr, tcsetattr
#include <sys/wait.h>

typedef struct s_token
{
    char	*token;
    struct s_token	*next;
    struct s_token	*prev;
    int              first;
}               t_token;

typedef struct s_info
{
    char	**envp;
    char	*pwd;
    char	**args;
    t_token	*token;
    int		exit_status;
}               t_info;

char *strTokR(char *str, const char *delim, char **savePtr);
char *strChr(const char *s, int c);
int strcSpn(const char *str, const char *set);
char **ft_split(char const *s, char c);

#endif