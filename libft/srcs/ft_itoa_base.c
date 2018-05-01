/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 22:45:50 by ssong             #+#    #+#             */
/*   Updated: 2018/03/16 14:16:35 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(uintmax_t n, int base)
{
	char	*str;
	size_t	c;
	char	symbol;

	if (base < 2 || base > 16)
		return (NULL);
	c = ft_countdigits_base(n, base);
	str = ft_strnew(c);
	str[c] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		symbol = n % base;
		if (symbol < 10)
			str[c - 1] = symbol + '0';
		if (symbol >= 10)
			str[c - 1] = symbol - 10 + 'a';
		n = n / base;
		c--;
	}
	return (str);
}
