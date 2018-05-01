/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexitoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 12:03:56 by ssong             #+#    #+#             */
/*   Updated: 2018/03/20 22:30:34 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_hexitoa(uintmax_t n)
{
	char	*str;
	size_t	c;
	char	symbol;

	c = ft_hex_countdigits(n);
	str = ft_strnew(c);
	if (!str)
		return (NULL);
	str[c] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		symbol = n % 16;
		if (symbol < 10)
			str[c - 1] = symbol + '0';
		if (symbol >= 10)
			str[c - 1] = symbol - 10 + 'a';
		n = n / 16;
		c--;
	}
	return (str);
}
