/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 22:20:45 by jinhokim          #+#    #+#             */
/*   Updated: 2020/10/02 20:31:16 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest2;
	char	*src2;
	size_t	i;

	dest2 = (char *)dest;
	src2 = (char *)src;
	i = -1;
	if (!dest && !src)
		return (NULL);
	if (dest2 > src2)
		while ((int)(--n) >= 0)
			dest2[n] = src2[n];
	else
		while (++i < n)
			dest2[i] = src2[i];
	return (dest);
}
