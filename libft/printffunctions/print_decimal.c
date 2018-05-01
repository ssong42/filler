/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_decimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:41:14 by ssong             #+#    #+#             */
/*   Updated: 2018/03/26 12:13:28 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*precision_deci(t_info *info, char *buf, intmax_t num)
{
	char *temp;

	if (num < 0 && info->space == 0)
	{
		buf[0] = '0';
		ft_putchar('-');
		info->printed++;
	}
	temp = ft_memalloc(info->precision + 1);
	temp = ft_memset(temp, '0', info->precision);
	temp = ft_strrcpy(temp, buf, ft_strlen(temp), ft_strlen(buf));
	ft_memdel((void **)&buf);
	return (temp);
}

static void		print_temp(t_info *info, char *buf, intmax_t num)
{
	char *temp;

	temp = ft_memalloc(info->space + 1);
	if (info->zero == 1 && info->precision == -1)
		temp = ft_memset(temp, '0', info->space);
	else
		temp = ft_memset(temp, ' ', info->space);
	if (info->left == 1)
		temp = ft_strncpy(temp, buf, ft_strlen(buf));
	if (info->left == 0)
		temp = ft_strrcpy(temp, buf, ft_strlen(temp), ft_strlen(buf));
	if (info->plus == 1 && info->zero == 1 && num > 0)
		temp[0] = '+';
	if (info->minus == 1 && info->zero == 1)
		temp[0] = '-';
	ft_putstr(temp);
	ft_memdel((void **)&temp);
}

static void		space_deci(t_info *info, char *buf, intmax_t num)
{
	if (info->precision == info->space && info->sign == 1)
	{
		ft_putchar(' ');
		info->printed++;
	}
	if (num < 0 && info->zero == 1)
	{
		info->minus = 1;
		buf[0] = '0';
	}
	if (info->plus == 1 && info->zero == 0)
		buf = ft_strcatnew("+", buf);
	info->printed += info->space;
	print_temp(info, buf, num);
	ft_memdel((void **)&buf);
}

static void		print_buf(t_info *info, char *buf, intmax_t num)
{
	if (info->plus == 1 && info->sign == 1)
		info->sign = 0;
	if (info->plus == 1 && num >= 0)
		ft_putchar('+');
	if (info->sign == 1 && num > 0)
		ft_putchar(' ');
	if ((info->plus == 1 || info->sign == 1) && num >= 0)
		info->printed++;
	info->printed += ft_strlen(buf);
	ft_putstr(buf);
}

t_info			*print_decimal(va_list *args, t_info *info)
{
	char		*buf;
	intmax_t	num;

	num = deci_modifier(info, args);
	buf = ft_intmaxt_itoa(num);
	if (!info->precision && !info->hash && num == 0)
		buf = ft_memset(buf, 0, ft_strlen(buf));
	if (info->precision > (int)ft_strlen(buf))
		buf = precision_deci(info, buf, num);
	if (info->space > 0)
		space_deci(info, buf, num);
	else
	{
		print_buf(info, buf, num);
		ft_memdel((void **)&buf);
	}
	return (info);
}
