/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:13:15 by ssong             #+#    #+#             */
/*   Updated: 2018/03/23 21:26:56 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *final, char *end)
{
	char *buf;

	buf = final;
	final = ft_strjoin(buf, end);
	ft_memdel((void **)&end);
	return (final);
}
