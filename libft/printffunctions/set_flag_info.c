/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flag_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 22:48:26 by ssong             #+#    #+#             */
/*   Updated: 2018/03/26 11:31:39 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool	double_modifiers(t_info **info, const char *str)
{
	if (str[(*info)->index] == 'l' & str[(*info)->index + 1] == 'l')
	{
		(*info)->modifier = 'm';
		(*info)->index++;
		return (1);
	}
	else if (str[(*info)->index] == 'h' && str[(*info)->index + 1] == 'h')
	{
		(*info)->modifier = 'a';
		(*info)->index++;
		return (1);
	}
	return (0);
}

t_info	*set_modifiers(t_info *info, const char *str)
{
	if (str[info->index] == 'l')
		info->modifier = 'l';
	else if (str[info->index] == 'h')
		info->modifier = 'h';
	else if (str[info->index] == 'j')
		info->modifier = 'j';
	else if (str[info->index] == 'z')
		info->modifier = 'z';
	return (info);
}

t_info	*set_flags(t_info *info, const char *str)
{
	if (str[info->index] == '-')
	{
		info->left = 1;
		info->minus = 1;
	}
	else if (str[info->index] == '+')
		info->plus = 1;
	else if (str[info->index] == '0' && info->left == 0)
		info->zero = 1;
	else if (str[info->index] == '.')
		info = parse_precision(str, info);
	else if (str[info->index] > '0' && str[info->index] <= '9')
		info = parse_space(str, info);
	else if (str[info->index] == '#')
		info->hash = 1;
	else if (str[info->index] == ' ')
		info->sign = 1;
	else if (str[info->index] == '*')
		info->width = 1;
	return (info);
}

t_info	*set_flag_info(t_info *info, const char *str, va_list *args)
{
	bool check;

	info->index++;
	while (info->index < info->end)
	{
		check = double_modifiers(&info, str);
		if (!check)
		{
			info = set_modifiers(info, str);
			info = set_flags(info, str);
		}
		info->index++;
	}
	if (info->width == 1 && info->space == 0)
		info->space = va_arg((*args), int);
	if (info->precision > info->space && info->space)
	{
		info->zero = 1;
		info->left = 0;
		info->space = info->precision;
	}
	return (info);
}
