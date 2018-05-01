/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_printed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 16:19:28 by ssong             #+#    #+#             */
/*   Updated: 2018/03/26 11:30:45 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_info	*print_printed(va_list *args, t_info *info)
{
	int		*num;

	num = va_arg((*args), int *);
	*num = info->printed;
	return (info);
}
