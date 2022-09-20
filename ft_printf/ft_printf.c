/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:56:18 by jinhokim          #+#    #+#             */
/*   Updated: 2022/09/02 15:44:18 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_type(va_list ap, t_flags *flags)
{
	int		ret;
	char	type;

	ret = 0;
	type = flags->type;
	if (type == 'c')
		ret = print_char(va_arg(ap, int), flags);
	else if (type == '%')
		ret = print_char('%', flags);
	else if (type == 's')
		ret = print_str(va_arg(ap, char *), flags);
	else if (type == 'd' || type == 'i')
		ret = print_nbr(va_arg(ap, int), flags);
	else if (type == 'x' || type == 'X' || type == 'u')
		ret = print_nbr(va_arg(ap, unsigned int), flags);
	else if (type == 'p')
		ret = print_nbr(va_arg(ap, unsigned long long), flags);
	return (ret);
}

void	check_width_and_prec(va_list ap,
		char *format, t_flags *flags, int i)
{
	if (ft_isdigit(format[i]))
	{
		if (flags->prec == -1)
			flags->width = flags->width * 10 + format[i] - 48;
		else
			flags->prec = flags->prec * 10 + format[i] - 48;
	}
	else if (format[i] == '*')
	{
		if (flags->prec == -1)
		{
			flags->width = va_arg(ap, int);
			if (flags->width < 0)
			{
				flags->minus = 1;
				flags->width *= -1;
			}
		}
		else
			flags->prec = va_arg(ap, int);
	}
}

int	parse_format_temp(va_list ap, t_flags *flags, int i, char *format)
{
	while (format[++i] != '\0' && !(ft_strchr("csdiupxX%", format[i])))
		check_flags(ap, format, flags, i);
	flags->type = format[i++];
	if ((flags->minus == 1 || flags->prec > -1) && flags->type != '%')
		flags->zero = 0;
	return (i);
}

int	parse_format(va_list ap, char *format)
{
	int		i;
	int		ret;
	t_flags	*flags;

	i = 0;
	ret = 0;
	flags = malloc(sizeof(t_flags) * 1);
	if (!(flags))
		return (-1);
	while (format[i] != '\0')
	{
		while (format[i] != '%' && format[i] != '\0')
			ret += ft_putchar(format[i++]);
		if (format[i] == '%')
		{
			init_flags(flags);
			i = parse_format_temp(ap, flags, i, format);
			ret += print_type(ap, flags);
		}
	}
	free(flags);
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	int		ret;
	va_list	ap;

	va_start(ap, format);
	ret = parse_format(ap, (char *)format);
	va_end(ap);
	return (ret);
}
