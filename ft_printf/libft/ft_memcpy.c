/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 01:08:48 by jinhokim          #+#    #+#             */
/*   Updated: 2020/10/02 20:21:15 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dest2;
	char	*src2;
	size_t	i;

	dest2 = dest;
	src2 = (char *)src;
	i = 0;
	if (dest2 == src2)
		return (dest2);
	while (i < n)
	{
		dest2[i] = src2[i];
		i++;
	}
	return (dest);
}
