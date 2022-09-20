/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 21:40:23 by jinhokim          #+#    #+#             */
/*   Updated: 2020/10/01 21:50:20 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst2;

	lst2 = *lst;
	if (lst || *lst)
	{
		while (*lst)
		{
			*lst = lst2->next;
			del(lst2->content);
			free(lst2);
			lst2 = *lst;
		}
	}
}
