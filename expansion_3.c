/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:40:06 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/12/21 13:40:06 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void check_pipes(t_data *data)
{
	t_token *current;

	if (!data->tokens)
		exit(1);
	current = data->tokens;
	while (current)
	{
		if (current->type == PIPE)
		{
			if (current->next)
			{
				if (current->next->type == PIPE)
					exit(1);
			}
			else
				exit(1);
		}
		current = current->next;
	}
}

void delete_spaces(t_data *data)
{
	t_token *current;

	if (!data->tokens)
		exit(1);
	current = data->tokens;
	while (current)
	{
		if (current->type == WS)
			current = relink_tokens(current, current->next, data);
		else
			current = current->next;
	}
}