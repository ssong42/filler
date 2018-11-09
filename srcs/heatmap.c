/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 11:59:06 by ssong             #+#    #+#             */
/*   Updated: 2018/11/09 12:00:10 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**  Taking average of coordinates. Sum of coordinate / total positions
**  status->totalenemies is counted in a separate function in initialize
**  game.
*/

void	find_centerofGravity(t_filler *status)
{
	int y;
	int x;

	y = 0;
	while (y < status->row)
	{
		x = 0;
		while (x < status->col)
		{
			if (status->map[y][x] == status->enemy)
			{
				status->centerY += y;
				status->centerX += x;
				status->totalenemies += 1;
			}
			x++;
		}
		y++;
	}
	status->centerY = status->centerY/status->totalenemies;
	status->centerX = status->centerX/status->totalenemies;
}

/*
**  Depending on location of the center of gravity, assign_heatvalue will
**  assign the corresponding value in respect to that center coordinates.
**
**  Equation is this:
**	Y2 = y coordinate of center of gravity
**	X2 = x coordinate of ...
**	Y1 = y coordinate current position being assigned
**	X1 = x coordinate current position being assigned. 
**  
**  	if (abs(Y2 - Y1) > abs(X2 - X1))
**		value = abs(Y2 - Y1)
**	else
**		value = abs(X2 - X1)
*/

void	assign_heatvalue(int y1, int x1, t_filler *status)
{
	if (ft_abs(10 - y1) > ft_abs(10 - x1))
		status->heatmap[y1][x1] = ft_abs(10 - y1);
	else
		status->heatmap[y1][x1] = ft_abs(10 - x1);
}

/*
**  Generate a heatmap from the map read and stored in memory
**  
**  Use function for testing:
**  print2dintarray(status->heatmap, status->row, status->col);
*/

void	generate_heatmap(t_filler *status)
{
	int i;
	int j;

	i = 0;
	status->heatmap = malloc(sizeof(int *) * status->row);
	while (i < status->row)
	{
		status->heatmap[i] = malloc(sizeof(int) * status->col);
		ft_bzeroint(status->heatmap[i], (unsigned int) status->col);
		j = 0;
		while (j < status->col)
		{
			assign_heatvalue(i, j, status);
			j++;
		}
		i++;
	}
	//print2dintarray(status->heatmap, status->row, status->col);
}
