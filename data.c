/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:00:42 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/12/16 21:00:42 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_data	*initData(void)
{
    t_data	*new;

    new = malloc(sizeof(t_data));
    if (!new)
        exit(2);
    new->args = NULL;
    new->user = NULL;
    new->env = NULL;
    new->cmds = NULL;
    new->tokens = NULL;
    return (new);
}