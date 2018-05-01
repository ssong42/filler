/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 10:42:53 by ssong             #+#    #+#             */
/*   Updated: 2018/03/26 11:31:47 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_functions	*set_fptr(t_functions *functions)
{
	functions[0] = (t_functions){'d', print_decimal};
	functions[1] = (t_functions){'D', print_decimal};
	functions[2] = (t_functions){'i', print_decimal};
	functions[3] = (t_functions){'%', print_char};
	functions[4] = (t_functions){'c', print_char};
	functions[5] = (t_functions){'C', print_char};
	functions[6] = (t_functions){'s', print_str};
	functions[7] = (t_functions){'S', print_wstr};
	functions[8] = (t_functions){'x', print_hexi};
	functions[9] = (t_functions){'X', print_hexi};
	functions[10] = (t_functions){'o', print_octal};
	functions[11] = (t_functions){'O', print_octal};
	functions[12] = (t_functions){'u', print_udecimal};
	functions[13] = (t_functions){'U', print_udecimal};
	functions[14] = (t_functions){'p', print_address};
	functions[15] = (t_functions){'n', print_printed};
	return (functions);
}

t_info		*find_call(t_functions *fct, t_info *info, va_list *args)
{
	int i;

	i = 0;
	while (fct[i].format != info->format)
		i++;
	info = fct[i].ptr(args, info);
	return (info);
}

t_data		*find_format(const char *str, t_data *data, va_list *args)
{
	data->info->end = data->info->index + 1;
	while (!isformat(str[data->info->end]) && str[data->info->end])
		data->info->end++;
	if (!str[data->info->end])
	{
		ft_putchar('%');
		data->info->index++;
		return (data);
	}
	set_flag_info(data->info, str, args);
	data->info->format = str[data->info->end];
	data->info = find_call(data->functions, data->info, args);
	data->info->index = data->info->end + 1;
	reset_info(data->info);
	return (data);
}

int			ft_printf(const char *str, ...)
{
	t_data	*data;
	va_list	args;
	int		chars;

	va_start(args, str);
	data = init_info();
	while (str[data->info->index])
	{
		if (str[data->info->index] == '%')
			data = find_format(str, data, &args);
		else
		{
			ft_putchar(str[data->info->index]);
			data->info->printed++;
			data->info->index++;
		}
	}
	chars = data->info->printed;
	ft_memdel((void **)&data->info);
	ft_memdel((void **)&data->functions);
	ft_memdel((void **)&data);
	return (chars);
}
