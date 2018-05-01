/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 20:42:56 by ssong             #+#    #+#             */
/*   Updated: 2018/05/01 16:54:37 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
 *  The things that are most important. I need to test every valid location for the token
 *  For a token to be valid these criteria need to be met:
 *  	* one piece of landing on one of the X's or O's
 *  	* not falling off the map
 *  	* not landing on the opponenet field
 *  Then once a piece is verified I can save it into the struct.
 *  Maybe after saving I can check the total distance travel to my destination
 *  I would like for my destination to be the opponenet's most newly placed pieces 
 *  		(if advantagious for them if not ...whatever)
 *  Then once the pieces are stored and distance traveled stored I will save that.
 *	This is phase one which is close off and chase, but phase 2 will be too slowly fill the encompassed zone.
 *  In order to find if an opponent is enclosed:
 *  	* check if my pieces reach from wall to wall and my opponenet is enclosed in it.
 *  	* make sure my algorithm will close it off by creating a barrier of new-put-piece - 1 from the x or y to
 *  		the closest wall
 *  	* immediately seal the largest zone with the piece im starting from. 
 *
 * TODO:
 * 		* start with storing the all possible valid moves
 * 		* verifying if they are valid
 * 		* save into struct after validation
 * 		* Check destination to goal or algorithm afterwards.
 *
 */


/*
 *	Get fancy as fuck with some sorting methods for your linked list. LAWL.
*/


/*
**  For a token to be valid these criteria need to be met:
**  	* one piece of token landing on one of my piece 'O' or 'X'
**  	* not falling off the map
**  	* not landing on the opponents pieces
**	I only need to check the taken parts of my token. Whether the empty
**		spots are taken or not taken by me or my opponent do not matter.
**	If I land on even one of my opponenets pieces my location is immediately
**		not valid
**	If I do not have exactly one match of my token and map then the piece is invalid.
*/

bool		valid_field(int x1, int y1, t_filler *status)
{
	int x2;
	int y2;
	int matches;
	
	matches = 0;
	y2 = 0;
	while (y2 < status->trow)
	{
		x2 = 0;
		while(x2 < status->tcol)
		{
			if (status->token[y2][x2] == '*')
			{
				if (status->map[y1 + y2][x1 + x2] == status->me)
					matches++;
				else if (status->map[y1 + y2][x1 + x2] == status->enemy)
					return (0);
			}
			x2++;
		}
		y2++;
	}
	if (matches == 1)
		return (1);
	return (0);
}

/*
** Create my new move and store it into my linked list
*/

t_moves		*store_move(int x, int y, int distance, t_moves *moves)
{
	t_moves *new;
	t_moves *cursor;

	cursor = moves;
	new = malloc(sizeof(t_moves));
	new->x = x;
	new->y = y;
	new->distance = distance;
	new->next = NULL;
	if (cursor == NULL)
		return(new);
	while (cursor->next != NULL)
		cursor = cursor->next;	
	cursor->next = new;
	return (moves);
}

/*
**	Iterate through every location and of my map and check if its a valid move
**	If the move is valid then find the distance this move travels towards desired
**	destination.
**	I will use this distance later to find the best possible move.
*/

t_moves		*find_moves(t_filler *status)	
{
	t_moves *moves;
	int y;
	int x;
	int distance;

	y = 0;
	distance = 0;
	moves = NULL;
	while (y + status->trow < status->row + 1)
	{
		x = 0;
		while (x + status->tcol < status->col + 1)
		{
			if(valid_field(x, y, status))
			{
				//distance = find_distance(x, y, status);
				moves = store_move(x, y, distance, moves);
			}
			x++;
		}
		y++;
	}
	return (moves);
}

int				in_game(t_filler *status)
{
	t_moves *moves;
	t_moves *cursor;

	initialize_game(status);
	moves = find_moves(status);
	cursor = moves;
	if (!moves)
	{
		ft_printf("%s\n", "no moves");
		return (0);
	}
	while (cursor != NULL)
	{
		printf("%d, %d\n", cursor->y, cursor->x);
		cursor = cursor->next;
	}
	return (0);
}

int main()
{
	t_filler *status;

	status = malloc(sizeof(t_filler));
	set_player(status);
	while(in_game(status));
	return (0);
}
