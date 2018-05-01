/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 09:51:33 by ssong             #+#    #+#             */
/*   Updated: 2018/03/20 22:33:02 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_long(long n)
{
	char	*str;
	size_t	c;
	size_t	neg;

	neg = 1;
	c = ft_lcountdigit(n);
	str = ft_strnew(c);
	if (!str)
		return (NULL);
	str[c] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		if (n < 0)
		{
			str[0] = '-';
			neg = -1;
		}
		str[c - 1] = ((n % 10) * neg) + '0';
		n = (n / 10);
		c--;
	}
	return (str);
}

char		*ft_itoa_float(double digit)
{
	double	deci;
	long	whole;
	char	*str;
	char	*str2;

	whole = 1;
	whole = digit * whole;
	str = ft_itoa_long(whole);
	deci = digit - (double)whole;
	if (deci < 0)
		deci *= -1;
	str2 = ft_itoa_deci(deci);
	str = ft_strjoinfree(str, str2);
	free(str2);
	return (str);
}
