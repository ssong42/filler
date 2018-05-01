/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 11:13:28 by ssong             #+#    #+#             */
/*   Updated: 2018/03/29 11:56:19 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft.h"

typedef struct	s_info
{
	int			hash;
	int			sign;
	char		format;
	int			zero;
	int			plus;
	int			minus;
	int			space;
	int			left;
	int			width;
	int			precision;
	int			modifier;
	int			printed;
	int			index;
	int			used;
	int			end;
}				t_info;

typedef struct	s_functions
{
	char	format;
	t_info	*(*ptr)(va_list *args, t_info *info);
}				t_functions;

typedef struct	s_data
{
	t_info		*info;
	t_functions *functions;
}				t_data;

t_info				*parse_space(const char *str, t_info *info);
t_info				*parse_precision(const char *str, t_info *info);
char				*ft_strrcpy(char *dest, char *src, int i, int a);
t_functions			*set_fptr(t_functions *functions);
t_info				*set_flag_info(t_info *info, const char *str, va_list *args);
t_info				*parse_precision(const char *str, t_info *info);
t_info				*print_decimal(va_list *args, t_info *info);
t_info				*print_udecimal(va_list *args, t_info *info);
t_info				*print_char(va_list *args, t_info *info);
t_info				*print_str(va_list *args, t_info *info);
t_info				*print_hexi(va_list *args, t_info *info);
t_info				*print_octal(va_list *args, t_info *info);
t_info				*print_address(va_list *args, t_info *info);
t_info				*print_printed(va_list *args, t_info *info);
t_info				*print_wstr(va_list *args, t_info *info);
t_data				*init_info(void);
t_info				*reset_info(t_info *info);
uintmax_t			udeci_modifiers(t_info *info, va_list *args);
intmax_t			deci_modifier(t_info *info, va_list *args);
uintmax_t			hexi_modifiers(t_info *info, va_list *args);
int					isformat(char c);
int					isplusminus(char c);
#endif
