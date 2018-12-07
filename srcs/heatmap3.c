/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 11:59:06 by ssong             #+#    #+#             */
/*   Updated: 2018/11/15 13:40:38 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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
	if (ft_abs(status->y2 - y1) > ft_abs(status->x2 - x1))
		status->heatmap[y1][x1] += ft_abs(status->y2 - y1);
	else
		status->heatmap[y1][x1] += ft_abs(status->x2 - x1);
}

/*
**	Initialize the heatmap
*/

void	init_heatmap(t_filler *status)
{
	int i;

	i = 0;
	status->heatmap = malloc(sizeof(int *) * status->row);
	while (i < status->row)
	{
		status->heatmap[i] = malloc(sizeof(int) * status->col);
		ft_bzeroint(status->heatmap[i], (unsigned int) status->col);
		i++;
	}
}

/*
**	If I have spotted an enemy piece, then I need to update the heatmap to add values according
** to that particular piece. This update has to go through every index in the 2d array.
*/

void	update_heatmap(t_filler *status)
{
	int y1;
	int x1;

	y1 = 0;
	while (y1 < status->row)
	{
		x1 = 0;
		while (x1 < status->col)
		{
			assign_heatvalue(y1, x1, status);
			x1++;
		}
		y1++;
	}
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
	init_heatmap(status);
	while (i < status->row)
	{
		j = 0;
		while (j < status->col)
		{
			if (status->map[i][j] == status->enemy || status->map[i][j] == status->enemy + 32)
			{
				status->x2 = j;
				status->y2 = i;
				update_heatmap(status);
			}
			j++;
		}
		i++;
	}
//	print2dintarray(status->heatmap, status->row, status->col);
}