/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_twodarray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 09:55:40 by ssong             #+#    #+#             */
/*   Updated: 2018/04/26 10:09:15 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_twodchararray(int row, int col)
{
	char **map;
	int i;

	i = 0;
	map = malloc(sizeof(char *) * row);
	if (!map)
		return (0);
	while(i < row)
	{
		map[i] = malloc(sizeof(char) * col + 1);
		i++;
	}
	return (map);
}
