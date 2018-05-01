/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wstring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 19:51:25 by ssong             #+#    #+#             */
/*   Updated: 2018/03/26 12:13:49 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_wstrlen(wchar_t *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_info		*print_wstr(va_list *args, t_info *info)
{
	wchar_t *str;

	str = ft_wstrdup(va_arg((*args), wchar_t *));
	if (!str)
	{
		ft_putstr("(null)");
		info->printed += 6;
		return (info);
	}
	else
	{
		ft_wputstr(str);
		info->printed += ft_wstrlen(str);
	}
	ft_memdel((void **)&str);
	return (info);
}
