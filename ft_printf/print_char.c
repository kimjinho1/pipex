/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:07:43 by jinhokim          #+#    #+#             */
/*   Updated: 2020/11/02 14:07:48 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_width(int width, int len, int zero)
{
	int		ret;

	ret = 0;
	while (len < width)
	{
		if (zero == 1)
			ft_putchar('0');
		else
			ft_putchar(' ');
		len++;
		ret++;
	}
	return (ret);
}

int	print_char(int c, t_flags *flags)
{
	int		ret;

	ret = 0;
	if (flags->type == '%' && flags->minus == 1)
		flags->zero = 0;
	if (flags->minus == 1)
		ret += ft_putchar(c);
	ret += put_width(flags->width, 1, flags->zero);
	if (flags->minus == 0)
		ret += ft_putchar(c);
	return (ret);
}
