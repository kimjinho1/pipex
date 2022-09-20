/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:46:41 by jinhokim          #+#    #+#             */
/*   Updated: 2022/09/02 15:09:25 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin2(char *s1, char *s2, int free_target)
{
	char	*str;
	int		i;
	int		j;
	int		s1_len;
	int		s2_len;

	i = -1;
	j = 0;
	s1_len = (int)ft_strlen(s1);
	s2_len = (int)ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!(str))
		return (NULL);
	while (++i < s1_len)
		str[i] = s1[i];
	while (j < s2_len)
		str[i++] = s2[j++];
	str[i] = '\0';
	if (free_target == 1 || free_target == 3)
		free(s1);
	if (free_target == 2 || free_target == 3)
		free(s2);
	return (str);
}
