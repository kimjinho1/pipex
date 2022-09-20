/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:07:29 by jinhokim          #+#    #+#             */
/*   Updated: 2022/09/02 15:34:06 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_minus_if_not_zero(t_flags *flags, char **buf)
{
	int		ret;

	ret = 0;
	if ((flags->type == 'i' || flags->type == 'd')
		&& flags->zero == 0 && flags->sign == -1)
	{
		*buf = ft_strjoin2("-", *buf, 2);
		ret = 1;
	}
	return (ret);
}

int	put_minus_if_zero(int buf_len, t_flags *flags, char **buf)
{
	int		ret;

	ret = 0;
	if (flags->sign == -1 && flags->zero == 1)
	{
		if (buf_len >= flags->width)
		{
			*buf = ft_strjoin2("-", *buf, 2);
			ret = 1;
		}
		else if (buf_len < flags->width)
			*buf[0] = '-';
	}
	return (ret);
}

int	put_prec_temp(int buf_len, int ret, char **buf)
{
	int	i;

	i = 0;
	(*buf)[ret] = '\0';
	while (buf_len + i < ret)
	{
		(*buf)[i] = '0';
		i++;
	}
	return (1);
}

int	put_prec_str(unsigned long long nbr, t_flags *flags, char **buf)
{
	int		buf_len;
	int		ret;
	int		i;

	buf_len = ft_nbrlen(nbr, flags);
	if (flags->prec > buf_len)
		ret = flags->prec;
	else
		ret = buf_len;
	*buf = (char *)malloc(sizeof(char) * ret + 1);
	if (!(*buf))
		return (0);
	put_prec_temp(buf_len, ret, buf);
	i = 1;
	if (nbr == 0 && flags->prec != 0)
		(*buf)[ret - i] = '0';
	while (nbr)
	{
		(*buf)[ret - i] = ft_baseset(flags->type)[nbr % flags->base];
		nbr /= flags->base;
		i++;
	}
	return (buf_len);
}

int	print_nbr(unsigned long long nbr, t_flags *flags)
{
	char	*buf;
	int		buf_len;
	int		ret;

	if (flags->type == 'x' || flags->type == 'X' || flags->type == 'p')
		flags->base = 16;
	if ((flags->type == 'd' || flags->type == 'i') && (int)nbr < 0)
	{
		flags->sign = -1;
		nbr = -nbr;
	}
	buf_len = put_prec_str(nbr, flags, &buf);
	buf_len += put_minus_if_not_zero(flags, &buf);
	if (flags->type == 'p')
		buf_len = put_pointer_prefix(&buf);
	ret = put_width_str(&buf, flags);
	ret += put_minus_if_zero(buf_len, flags, &buf);
	ft_putstr(buf);
	free(buf);
	return (ret);
}
