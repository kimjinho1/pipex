/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 13:47:05 by jinhokim          #+#    #+#             */
/*   Updated: 2022/09/01 16:24:51 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(int n)
{
	int			len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	make_result(char *result, int len, int i, int n)
{
	while (len-- > i)
	{
		if (n < 0)
		{
			result[len] = '0' + n % 10 * (-1);
			n = n / 10;
		}
		else
		{
			result[len] = '0' + n % 10;
			n = n / 10;
		}
	}
}

char	*ft_itoa(int n)
{
	size_t	len;
	size_t	i;
	char	*result;

	len = ft_intlen(n);
	result = (char *)malloc(len + 1);
	if (!(result))
		return (NULL);
	result[len] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		i = 1;
	}
	else
		i = 0;
	make_result(result, len, i, n);
	return (result);
}
