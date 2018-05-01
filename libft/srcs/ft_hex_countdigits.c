/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_countdigits.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 19:46:11 by ssong             #+#    #+#             */
/*   Updated: 2018/03/20 22:31:46 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hex2_countdigits(uintmax_t n)
{
	int			count;
	uintmax_t	base;

	base = 16;
	count = 3;
	while (n / base >= 1)
	{
		count++;
		base = base * 16;
	}
	return (count);
}

int	ft_hex_countdigits(uintmax_t n)
{
	int			count;
	uintmax_t	base;

	base = 16;
	count = 0;
	if (n == 0)
		count = 1;
	while (n != 0)
	{
		count++;
		n = n / 16;
	}
	return (count);
}
