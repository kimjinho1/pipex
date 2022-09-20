/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 18:36:16 by jinhokim          #+#    #+#             */
/*   Updated: 2022/09/01 15:54:08 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	return_index(const char *nptr)
{
	int	i;

	i = 0;
	while (42)
	{
		if (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
			|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
			i++;
		else
			break ;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	n;

	i = return_index(nptr);
	sign = 1;
	n = 0;
	if (nptr[i] == '-')
		sign *= -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (n * sign > 2147483647)
			return (-1);
		else if (n * sign < -2147483648)
			return (0);
		else
			n = n * 10 + (nptr[i] - '0');
		i++;
	}
	return (n * sign);
}
