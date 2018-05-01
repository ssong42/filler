/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 22:44:32 by ssong             #+#    #+#             */
/*   Updated: 2018/03/26 12:13:19 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_info	*print_address(va_list *args, t_info *info)
{
	uintmax_t	digit;
	char		*str;

	digit = va_arg((*args), uintmax_t);
	str = ft_strjoin("0x", ft_hexitoa(digit));
	ft_putstr(str);
	info->printed += ft_strlen(str);
	ft_memdel((void **)&str);
	return (info);
}
