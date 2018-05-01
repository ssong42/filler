/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 11:30:11 by ssong             #+#    #+#             */
/*   Updated: 2018/03/26 11:30:37 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*create_space(t_info *info)
{
	char	*temp;

	temp = ft_memalloc(info->space + 1);
	if (info->zero == 1)
		temp = ft_memset(temp, '0', info->space);
	else
		temp = ft_memset(temp, ' ', info->space);
	return (temp);
}

static t_info	*hexi_space(t_info *info, char *buf, uintmax_t num)
{
	char		*temp;

	temp = create_space(info);
	if (info->hash == 1 && num > 0)
	{
		if (info->zero == 1)
		{
			temp[0] = '0';
			temp[1] = 'x';
		}
		else
			buf = ft_strjoin("0x", buf);
	}
	if (info->left == 1)
		temp = ft_strncpy(temp, buf, ft_strlen(buf));
	else if (info->left == 0)
		temp = ft_strrcpy(temp, buf, ft_strlen(temp), ft_strlen(buf));
	ft_putstr(temp);
	if (info->hash == 1 && info->zero == 0)
		ft_memdel((void **)&buf);
	ft_memdel((void **)&temp);
	info->printed += info->space;
	return (info);
}

static t_info	*hexi_buf(t_info *info, char *buf, uintmax_t num)
{
	char	*temp;

	temp = NULL;
	if (info->plus == 1)
		ft_putchar('+');
	else if (info->sign == 1)
		ft_putchar(' ');
	if (info->plus == 1 || info->sign == 1)
		info->printed++;
	if (info->hash == 1 && num > 0)
	{
		if (info->format == 'x')
			temp = ft_strjoin("0x", buf);
		else
			temp = ft_strjoin("0X", buf);
		info->printed += ft_strlen(temp);
		ft_putstr(temp);
		ft_memdel((void **)&temp);
	}
	else
	{
		info->printed += ft_strlen(buf);
		ft_putstr(buf);
	}
	return (info);
}

t_info			*print_hexi(va_list *args, t_info *info)
{
	uintmax_t	num;
	char		*buf;

	num = hexi_modifiers(info, args);
	if (info->format == 'x')
		buf = ft_hexitoa(num);
	else
		buf = ft_hex_itoa(num);
	if (!info->precision)
		buf = ft_memset(buf, 0, ft_strlen(buf));
	if (info->space > 0 && info->space > (int)ft_strlen(buf))
		info = hexi_space(info, buf, num);
	else
		info = hexi_buf(info, buf, num);
	ft_memdel((void **)&buf);
	return (info);
}
