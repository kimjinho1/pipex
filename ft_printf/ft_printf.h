/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:57:47 by jinhokim          #+#    #+#             */
/*   Updated: 2022/09/08 11:24:32 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "./libft/libft.h"

typedef struct s_flags
{
	int			minus;
	int			zero;
	int			width;
	int			prec;
	char		type;
	int			base;
	int			sign;
}				t_flags;

int				print_char(int c, t_flags *flags);
int				put_width(int width, int len, int zero);

int				print_str(char *str, t_flags *flags);
char			*parse_buf(char *str, int end, int len);
int				put_width_str(char **buf, t_flags *flags);

int				print_nbr(unsigned long long nbr, t_flags *flags);
int				put_prec_str(unsigned long long nbr, t_flags *flags,
					char **buf);
int				put_prec_temp(int buf_len, int ret, char **buf);
int				put_minus_if_not_zero(t_flags *flags, char **buf);
int				put_minus_if_zero(int buf_len, t_flags *flags, char **buf);

void			init_flags(t_flags *flags);
int				ft_nbrlen(unsigned long long nbr, t_flags *flags);
char			*ft_baseset(char type);
void			check_flags(va_list ap, char *format, t_flags *flags, int i);
int				put_pointer_prefix(char **buf);

int				ft_printf(const char *format, ...);
int				parse_format(va_list ap, char *format);
int				parse_format_temp(va_list ap, t_flags *flags,
					int i, char *format);
void			check_width_and_prec(va_list ap,
					char *format, t_flags *flags, int i);
int				print_type(va_list ap, t_flags *flags);

#endif
