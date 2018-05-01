/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 11:04:18 by ssong             #+#    #+#             */
/*   Updated: 2018/03/26 11:30:23 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_info	*parse_space(const char *str, t_info *info)
{
	int		a;
	char	*temp;

	a = info->index;
	while (ft_isdigit(str[a]))
		a++;
	temp = extract_string(str, info->index, a);
	info->index = a - 1;
	info->space = ft_atoi(temp);
	free(temp);
	return (info);
}

t_info	*parse_precision(const char *str, t_info *info)
{
	int		a;
	char	*temp;

	info->index++;
	a = info->index;
	if (!ft_isdigit(str[a]))
	{
		info->index = a - 1;
		info->precision = 0;
		return (info);
	}
	while (ft_isdigit(str[a]))
		a++;
	temp = extract_string(str, info->index, a);
	info->index = a - 1;
	info->precision = ft_atoi(temp);
	free(temp);
	return (info);
}
