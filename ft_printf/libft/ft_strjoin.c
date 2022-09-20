/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 01:19:27 by jinhokim          #+#    #+#             */
/*   Updated: 2022/09/01 14:33:32 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;
	int		s1_len;
	int		s2_len;

	i = 0;
	j = 0;
	if (s1 == 0 || s2 == 0)
		return (NULL);
	s1_len = (int)ft_strlen(s1);
	s2_len = (int)ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!(str))
		return (NULL);
	while (i < s1_len)
	{
		str[i] = s1[i];
		i++;
	}
	while (j < s2_len)
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
