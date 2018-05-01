/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intmaxt_itoa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 18:23:15 by ssong             #+#    #+#             */
/*   Updated: 2018/03/20 22:36:26 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_intmaxt_countdigit(intmax_t n)
{
	int	c;

	c = 0;
	if (n == 0)
		c++;
	else if (n < 0)
		c++;
	while (n != 0)
	{
		n = n / 10;
		c++;
	}
	return (c);
}

char	*ft_intmaxt_itoa(intmax_t n)
{
	char		*str;
	int			c;
	intmax_t	neg;

	neg = 1;
	c = ft_intmaxt_countdigit(n);
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
