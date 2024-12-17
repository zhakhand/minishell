/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:37:22 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/05/01 14:14:42 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_content;
	t_list	*current;

	new_lst = NULL;
	while (lst && f && del)
	{
		new_content = f(lst->content);
		current = ft_lstnew(new_content);
		if (current == NULL)
		{
			del(new_content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		else
		{
			ft_lstadd_back(&new_lst, current);
			lst = lst->next;
		}
	}
	return (new_lst);
}
