/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_modifiers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 23:07:48 by ssong             #+#    #+#             */
/*   Updated: 2018/03/29 11:44:48 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	deci_modifier(t_info *info, va_list *args)
{
	intmax_t num;

	num = 0;
	if (info->format == 'D')
		num = va_arg((*args), long int);
	else if (info->modifier == 0)
		num = (intmax_t)va_arg((*args), int);
	else if (info->format == 'd' && info->modifier == 'l')
		num = (intmax_t)va_arg((*args), long int);
	else if (info->modifier == 'm')
		num = (intmax_t)va_arg((*args), long long int);
	else if (info->modifier == 'h')
		num = (intmax_t)(short)va_arg((*args), int);
	else if (info->modifier == 'a')
		num = (intmax_t)(char)va_arg((*args), int);
	else if (info->modifier == 'j')
		num = (intmax_t)va_arg((*args), intmax_t);
	else if (info->modifier == 'z')
		num = (intmax_t)va_arg((*args), size_t);
	return (num);
}

uintmax_t	hexi_modifiers(t_info *info, va_list *args)
{
	uintmax_t num;

	num = 0;
	if (info->modifier == 0)
		num = (uintmax_t)va_arg((*args), unsigned int);
	else if (info->modifier == 'l')
		num = (uintmax_t)va_arg((*args), unsigned long int);
	else if (info->modifier == 'm')
		num = (uintmax_t)va_arg((*args), unsigned long long int);
	else if (info->modifier == 'h')
		num = (uintmax_t)(unsigned short)va_arg((*args), unsigned int);
	else if (info->modifier == 'a')
		num = (uintmax_t)(unsigned char)va_arg((*args), unsigned int);
	else if (info->modifier == 'j')
		num = va_arg((*args), uintmax_t);
	else if (info->modifier == 'z')
		num = (uintmax_t)va_arg((*args), size_t);
	return (num);
}

uintmax_t	udeci_modifiers(t_info *info, va_list *args)
{
	uintmax_t num;

	if (info->modifier == 0 && info->format == 'u')
		num = (uintmax_t)va_arg((*args), unsigned int);
	if (info->modifier == 0 && info->format == 'U')
		num = (uintmax_t)va_arg((*args), unsigned long int);
	else if (info->modifier == 'l')
		num = (uintmax_t)va_arg((*args), unsigned long int);
	else if (info->modifier == 'm')
		num = (uintmax_t)va_arg((*args), unsigned long long int);
	else if (info->modifier == 'h')
		num = (uintmax_t)va_arg((*args), unsigned long int);
	else if (info->modifier == 'a')
		num = (uintmax_t)(unsigned char)va_arg((*args), unsigned int);
	else if (info->modifier == 'j')
		num = va_arg((*args), uintmax_t);
	else if (info->modifier == 'z')
		num = (uintmax_t)va_arg((*args), size_t);
	return (num);
}
