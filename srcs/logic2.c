/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:30:42 by ssong             #+#    #+#             */
/*   Updated: 2018/12/13 15:30:43 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	if status->init is equal to zero or not initialized
**	we need to find our piece dawg.
*/

void	find_origin(t_filler *status)
{
	if (status->init == 0)
	{
		int y1;
		int x1;

		y1 = -1;
		while (++y1 < status->row)
		{
			x1 = -1;
			while (++x1 < status->col)
			{
				if (status->map[y1][x1] == status->me) 
				{
					status->initx = x1;
					status->inity = y1;
				}
				else if (status->map[y1][x1] == status->enemy) 
				{
					status->initex = x1;
					status->initey = y1;
				}
			}
		}
		status->init = 1;
	}
}

/*
** The corresponding player number is sent to the corresponding player,
** so all I need to do is search if I am player 1. If I am then I am character
** 'o', and if not then I am 'x'. I am also setting it for my opponent.
*/

void	set_player(t_filler *status)
{
	char *line;

	line = 0;
	if(!get_next_filler(STDIN_FILENO, &line))
		exit(0);
	if (!ft_strcmp(line + 11, "1"))
	{
		status->me = 'O';
		status->enemy = 'X';
	}
	else
	{
		status->me = 'X';
		status->enemy = 'O';
	}
	free(line);
}
/*
**	if stage 0 check if the thing is hitting left
**	if stage 1 check if the thing is hitting top right
**	if stage 2 then booyeah
*/

void	set_stage(t_filler *status)
{
	if (status->stage == 0)
	{
		if (leftwall_touching(status))
			status->stage++;
	}
	else if (status->stage == 1)
	{
		if (rightwall_touching(status))
			status->stage++;
	}
}