/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 02:32:31 by jinhokim          #+#    #+#             */
/*   Updated: 2022/09/01 14:32:53 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_word_count(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			cnt++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (cnt);
}

char	*ft_word_make(char *word, char const *s, int k, int word_len)
{
	int		i;

	i = 0;
	while (word_len > 0)
		word[i++] = s[k - word_len--];
	word[i] = '\0';
	return (word);
}

char	**ft_split2(char **result, char const *s, char c, int word_num)
{
	int		i;
	int		k;
	int		word_len;

	i = 0;
	k = 0;
	word_len = 0;
	while (s[k] && i < word_num)
	{
		while (s[k] && s[k] == c)
			k++;
		while (s[k] && s[k] != c)
		{
			k++;
			word_len++;
		}
		result[i] = (char *)malloc(sizeof(char) * (word_len + 1));
		if (!(result[i]))
			return (NULL);
		ft_word_make(result[i], s, k, word_len);
		word_len = 0;
		i++;
	}
	result[i] = 0;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		word_num;
	char	**result;

	if (s == 0)
		return (NULL);
	word_num = ft_word_count(s, c);
	result = (char **)malloc(sizeof(char *) * (word_num + 1));
	if (!(result))
		return (NULL);
	ft_split2(result, s, c, word_num);
	return (result);
}
