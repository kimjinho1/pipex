/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:08:04 by jinhokim          #+#    #+#             */
/*   Updated: 2022/09/02 14:49:58 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*parse_buf(char *str, int end, int len)
{
	int		i;
	char	*buf;

	if (end > len)
		end = len;
	buf = (char *)malloc(sizeof(char) * end + 1);
	if (!(buf))
		return (NULL);
	i = 0;
	while (i < end)
	{
		buf[i] = str[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

int	put_width_str(char **buf, t_flags *flags)
{
	char	*width;
	int		i;

	if (flags->width <= (int)ft_strlen(*buf))
		return ((int)ft_strlen(*buf));
	width = (char *)malloc(sizeof(char) * (flags->width - ft_strlen(*buf) + 1));
	i = 0;
	while ((size_t)i < flags->width - ft_strlen(*buf))
	{
		if (flags->zero == 1)
			width[i] = '0';
		else
			width[i] = ' ';
		i++;
	}
	width[i] = '\0';
	if (flags->minus == 0)
		*buf = ft_strjoin2(width, *buf, 3);
	else
		*buf = ft_strjoin2(*buf, width, 3);
	return (flags->width);
}

int	print_str(char *str, t_flags *flags)
{
	int		ret;
	char	*buf;

	ret = 0;
	if (str == NULL)
		str = "(null)";
	if (flags->prec == -1 || (size_t)flags->prec > ft_strlen(str))
		flags->prec = ft_strlen(str);
	buf = parse_buf(str, flags->prec, ft_strlen(str));
	ret = put_width_str(&buf, flags);
	ft_putstr(buf);
	free(buf);
	return (ret);
}
