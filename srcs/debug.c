/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:35:13 by ssong             #+#    #+#             */
/*   Updated: 2018/11/09 12:41:34 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	print2darray(char **map)
{
	int i;

	i = 0;
	while (map[i] != NULL)
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
}

void	print2dintarray(int **map, int r, int c)
{
	int i;
	int j;

	i = 0;
	while (i < r)
	{
		j = 0; 
		while (j < c)
		{
			ft_printf("%-2d ", map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
