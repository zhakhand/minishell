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

#endif