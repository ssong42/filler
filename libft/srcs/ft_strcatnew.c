/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcatnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 15:03:55 by ssong             #+#    #+#             */
/*   Updated: 2018/03/21 22:48:17 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcatnew(char *str, char *cat)
{
	int		i;
	char	*mew;

	i = (int)ft_strlen(str) + (int)ft_strlen(cat);
	mew = malloc(sizeof(char) * i + 1);
	if (mew == 0)
		return (0);
	mew = ft_memset(mew, 0, i);
	mew = ft_strcpy(mew, str);
	mew = ft_strcat(mew, cat);
	ft_memdel((void **)&cat);
	return (mew);
}
