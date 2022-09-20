/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 21:23:46 by jinhokim          #+#    #+#             */
/*   Updated: 2020/10/01 21:34:27 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst2;

	lst2 = *lst;
	if (!(*lst))
		*lst = new;
	else
	{
		while (lst2->next)
			lst2 = lst2->next;
		lst2->next = new;
	}
}
