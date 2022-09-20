/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 19:34:26 by jinhokim          #+#    #+#             */
/*   Updated: 2022/09/01 14:41:14 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(*ptr) * nmemb * size);
	if (!(ptr))
		return (NULL);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}
