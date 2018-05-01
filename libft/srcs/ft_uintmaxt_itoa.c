/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintmaxt_itoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 10:51:30 by ssong             #+#    #+#             */
/*   Updated: 2018/03/16 22:34:17 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_uintmaxt_countdigits(uintmax_t n)
{
	int		c;

	c = 0;
	if (n == 0)
		c++;
	while (n != 0)
	{
		n = n / 10;
		c++;
	}
	return (c);
}

char	*ft_uintmaxt_itoa(uintmax_t n)
{
	char	*str;
	int		c;

	c = ft_uintmaxt_countdigits(n);
	str = ft_strnew(c);
	if (!str)
		return (NULL);
	str[c] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		str[c - 1] = ((n % 10)) + '0';
		n = (n / 10);
		c--;
	}
	return (str);
}
