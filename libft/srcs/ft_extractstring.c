/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extractstring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 22:42:22 by ssong             #+#    #+#             */
/*   Updated: 2018/03/23 20:21:01 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*extract_string(const char *str, int start, int end)
{
	char	*temp;
	int		i;
	int		iter;

	i = 0;
	iter = start;
	temp = ft_strnew(end - start);
	while (i < (end - iter))
	{
		temp[i] = str[start];
		start++;
		i++;
	}
	temp[i] = 0;
	return (temp);
}
