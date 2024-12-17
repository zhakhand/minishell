/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:36:41 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/05/01 13:53:27 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			current = *lst;
			while (current->next)
				current = current->next;
			current->next = new;
		}
	}
}
