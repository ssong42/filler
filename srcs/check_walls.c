/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:20:28 by ssong             #+#    #+#             */
/*   Updated: 2018/12/13 15:20:31 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	leftwall_touching(t_filler *status)
{
	int y1;

	y1 = 0;
	while (y1 < status->row)
	{
		if (status->map[y1][0] == status->me || status->map[y1][0] == status->me + 32) 
			return (1);
		y1++;
	}
	return (0);
}

int	rightwall_touching(t_filler *status)
{
	int y1;

	y1 = 0;
	while (y1 < status->row)
	{
		if (status->map[y1][status->col - 1] == status->me || status->map[y1][status->col - 1] == status->me + 32) 
			return (1);
		y1++;
	}
	return (0);
}

int	topwall_touching(t_filler *status)
{
	int x1;

	x1 = 0;
	while (x1 < status->col)
	{
		if (status->map[0][x1] == status->me || status->map[0][x1] == status->me + 32) 
			return (1);
		x1++;
	}
	return (0);
}

int	bottomwall_touching(t_filler *status)
{
	int x1;

	x1 = 0;
	while (x1 < status->col)
	{
		if (status->map[status->row - 1][x1] == status->me || status->map[status->row - 1][x1] == status->me + 32) 
			return (1);
		x1++;
	}
	return (0);
}
