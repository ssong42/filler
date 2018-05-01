/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_deci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 10:42:48 by ssong             #+#    #+#             */
/*   Updated: 2018/03/14 18:22:33 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_deci(double digit)
{
	int		num;
	double	base;
	int		i;
	char	*str;

	str = malloc(sizeof(char) * 8);
	str[7] = 0;
	str[0] = '.';
	i = 1;
	base = .1;
	while (i < 7)
	{
		num = digit / base;
		str[i] = num + '0';
		digit = digit - (base * (double)num);
		base = base * .1;
		i++;
	}
	return (str);
}
