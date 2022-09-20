/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:55:55 by jinhokim          #+#    #+#             */
/*   Updated: 2022/09/02 15:40:01 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_flags(t_flags *flags)
{
	flags->minus = 0;
	flags->zero = 0;
	flags->width = 0;
	flags->prec = -1;
	flags->type = 0;
	flags->base = 10;
	flags->sign = 1;
}

int	ft_nbrlen(unsigned long long nbr, t_flags *flags)
{
	int		i;

	if (nbr == 0 && flags->prec != 0)
		return (1);
	i = 0;
	while (nbr)
	{
		i++;
		nbr /= flags->base;
	}
	return (i);
}

char	*ft_baseset(char type)
{
	if (type == 'u' || type == 'd' || type == 'i')
		return ("0123456789");
	else if (type == 'x' || type == 'p')
		return ("0123456789abcdef");
	else if (type == 'X')
		return ("0123456789ABCDEF");
	return (0);
}

void	check_flags(va_list ap, char *format, t_flags *flags, int i)
{
	if (format[i] == '0' && flags->width == 0 && flags->prec == -1)
		flags->zero = 1;
	else if (format[i] == '-')
		flags->minus = 1;
	else if (format[i] == '.')
		flags->prec = 0;
	else if (ft_isdigit(format[i]) || format[i] == '*')
		check_width_and_prec(ap, format, flags, i);
}

int	put_pointer_prefix(char **buf)
{
	*buf = ft_strjoin2("0x", *buf, 2);
	return (ft_strlen(*buf));
}
