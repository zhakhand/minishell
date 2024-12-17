/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:36:59 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/05/01 14:05:27 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;

	if (lst && del)
	{
		while (*lst)
		{
			curr = (*lst)->next;
			del((*lst)->content);
			free(*lst);
			*lst = curr;
		}
		*lst = NULL;
	}
}
