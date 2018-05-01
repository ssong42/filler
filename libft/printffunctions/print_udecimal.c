/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_udecimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 22:27:34 by ssong             #+#    #+#             */
/*   Updated: 2018/03/26 11:31:23 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*udeci_precision(char *buf, t_info *info)
{
	char	*temp;

	temp = NULL;
	if (info->precision > (int)ft_strlen(buf))
	{
		temp = ft_memalloc(info->precision + 1);
		temp = ft_memset(temp, '0', info->precision);
		temp = ft_strrcpy(temp, buf, ft_strlen(temp), ft_strlen(buf));
		ft_memdel((void **)&buf);
		return (temp);
	}
	return (buf);
}

static t_info	*udeci_space(char *buf, t_info *info)
{
	char *temp;

	if (info->space < (int)ft_strlen(buf))
		info->space = 0;
	if (info->space > 0)
	{
		info->printed += info->space;
		temp = ft_memalloc(info->space + 1);
		if (info->zero == 1)
			temp = ft_memset(temp, '0', info->space);
		else
			temp = ft_memset(temp, ' ', info->space);
		if (info->left == 1)
			temp = ft_strncpy(temp, buf, ft_strlen(buf));
		if (info->left == 0)
			temp = ft_strrcpy(temp, buf, ft_strlen(temp), ft_strlen(buf));
		ft_putstr(temp);
		ft_memdel((void **)&temp);
	}
	return (info);
}

t_info			*print_udecimal(va_list *args, t_info *info)
{
	intmax_t	num;
	char		*buf;

	if (info->modifier == 0 && info->format == 'u')
		num = (uintmax_t)va_arg((*args), unsigned int);
	else if (info->modifier == 0 && info->format == 'U')
		num = (uintmax_t)va_arg((*args), unsigned long int);
	else
		num = udeci_modifiers(info, args);
	buf = ft_uintmaxt_itoa(num);
	buf = udeci_precision(buf, info);
	if (info->space > 0)
		info = udeci_space(buf, info);
	if (info->space == 0)
	{
		info->printed += ft_strlen(buf);
		ft_putstr(buf);
	}
	ft_memdel((void **)&buf);
	return (info);
}
