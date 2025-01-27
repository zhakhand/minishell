/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:59:26 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/07/22 11:22:44 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <sys/stat.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*gnl_strdup(char *s);
char	*gnl_strncpy(char *d, char *s, int l);
char	*gnl_strcat(char *d, char *s);
char	*gnl_strchr(char	*s, char c);
int		gnl_strlen(char *s);
void	gnl_free(char **a);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 21
# endif

#endif