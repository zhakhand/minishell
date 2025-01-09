/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:59:21 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/07/22 11:32:42 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strdup(char *s)
{
	char	*d;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	d = malloc(gnl_strlen(s) + 1);
	if (!d)
		return (NULL);
	while (s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

static char	*do_other_stuff(char **r)
{
	char	*l;

	l = NULL;
	if (gnl_strlen(*r) > 0)
		l = gnl_strdup(*r);
	gnl_free(r);
	*r = NULL;
	if (!l)
		return (NULL);
	return (l);
}

static char	*do_something_different(char *n_l_p, char **r)
{
	int		l_l;
	char	*n_r;
	char	*l;

	l_l = (n_l_p - *r) + 1;
	l = malloc(l_l + 1);
	if (!l)
		return (gnl_free(r), NULL);
	l = gnl_strncpy(l, *r, l_l);
	l[l_l] = '\0';
	n_r = gnl_strdup(n_l_p + 1);
	gnl_free(r);
	if (!n_r)
		return (gnl_free(&l), gnl_free(&n_l_p), NULL);
	*r = n_r;
	n_r = NULL;
	return (l);
}

static char	*do_something(int fd, int *b_r, char *r)
{
	char	*t;
	char	*b;

	b = malloc(BUFFER_SIZE + 1);
	if (!b)
		return (gnl_free(&r), NULL);
	*b_r = read(fd, b, BUFFER_SIZE);
	if (*b_r < 0)
		return (gnl_free(&r), gnl_free(&b), NULL);
	b[*b_r] = '\0';
	if (r)
	{
		t = malloc(gnl_strlen(r) + *b_r + 1);
		if (!t)
			return (gnl_free(&r), gnl_free(&b), NULL);
		t = gnl_strncpy(t, r, gnl_strlen(r) + 1);
		t = gnl_strcat(t, b);
		gnl_free(&b);
		gnl_free(&r);
		r = t;
		return (r);
	}
	r = gnl_strdup(b);
	gnl_free(&b);
	return (r);
}

char	*get_next_line(int fd)
{
	static char	*r;
	char		*l;
	int			b_r;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		r = do_something(fd, &b_r, r);
		if (!r)
			return (NULL);
		l = gnl_strchr(r, '\n');
		if (l)
		{
			l = do_something_different(l, &r);
			if (!l)
				return (gnl_free(&r), NULL);
			return (l);
		}
		if (b_r < BUFFER_SIZE)
		{
			l = do_other_stuff(&r);
			return (l);
		}
	}
}
