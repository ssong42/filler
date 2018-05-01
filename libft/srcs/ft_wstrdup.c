/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 19:59:12 by ssong             #+#    #+#             */
/*   Updated: 2018/03/20 22:04:36 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

wchar_t		*ft_wstrdup(wchar_t *str)
{
	int		i;
	wchar_t	*s2;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i])
		i++;
	s2 = malloc(sizeof(wchar_t) * (i + 1));
	i = 0;
	while (str[i])
	{
		s2[i] = str[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
