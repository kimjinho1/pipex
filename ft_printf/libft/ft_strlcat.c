/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 23:48:36 by jinhokim          #+#    #+#             */
/*   Updated: 2020/09/29 00:53:58 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		j;
	size_t	k;

	i = ft_strlen(dst);
	j = 0;
	if (size < i)
		k = size;
	else
		k = i;
	while (src[j] && i < size - 1 && size != 0)
		dst[i++] = src[j++];
	while (src[j] != '\0')
		j++;
	dst[i] = '\0';
	return (k + j);
}
