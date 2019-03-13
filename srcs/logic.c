/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:22:17 by ssong             #+#    #+#             */
/*   Updated: 2018/12/13 15:22:19 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	Assign to corner from a specific point on a map.
*/

void	assigncorner(t_filler *status)
{
	if (status->stage == 2)
	{
		status->y2 = status->row - 1;
		status->x2 = 0;
	}
	else if (status->stage == 3)
	{
		status->y2 = status->row - 1;
		status->x2 = status->col - 1;
	}
	else if (status->stage == 4)
	{
		status->y2 = status->row / 2;
		status->x2 = status->col / 2;
	}
	assigncorner2(status);
	status->stage++;
}

void	assigncorner2(t_filler *status)
{
	if (status->stage == 5)
	{
		status->y2 = 0;
		status->x2 = 0;
	}
	else if (status->stage == 6)
	{
		status->y2 = 0;
		status->x2 = status->col - 1;
	}
	else
	{
		status->stage = 1;
		find_centerofgravity(status);
	}
}

/*
**	Set Destination. sets destination. Depending on the stage it will provide
**	x and y coordinates for the alogrith to try to go to.
*/

void	set_destination(t_filler *status)
{
	if (status->stage == 0)
	{
		status->x2 = 0;
		status->y2 = status->inity;
	}
	else if (status->stage == 1)
	{
		status->x2 = status->col - 1;
		status->y2 = 0;
	}
	else if (status->stage >= 2)
	{
		AssignCorner(status);
	}
}

void	set_stage2(t_filler *status)
{
	if (status->stage == 0)
	{
		if (topwall_touching(status))
			status->stage++;
	}
	else if (status->stage == 1)
	{
		if (bottomwall_touching(status))
			status->stage++;
	}
}

void	set_destination2(t_filler *status)
{
	if (status->stage == 0)
	{
		status->x2 = status->col/2;
		status->y2 = 0;
	}
	else if (status->stage == 1)
	{
		status->x2 = status->col/2;
		status->y2 = status->row;
	}
	else if (status->stage >= 2)
	{
		assigncorner(status);
	}
}