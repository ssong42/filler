/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 20:42:56 by ssong             #+#    #+#             */
/*   Updated: 2018/11/10 17:23:26 by ssong            ###   ########.fr       */
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
**	Create my new move and store it into my linked list
*/

t_moves		*store_move(int x, int y, int points, t_moves *moves)
{
	t_moves *new;
	t_moves *cursor;

	cursor = moves;
	new = malloc(sizeof(t_moves));
	new->x = x;
	new->y = y;
	new->points = points;
	new->next = NULL;
	if (cursor == NULL)
		return(new);
	while (cursor->next != NULL)
		cursor = cursor->next;	
	cursor->next = new;
	return (moves);
}

/*
**	Find total points for particular move
*/

int		find_points(int x1, int y1, t_filler *status)
{
	int x2;
	int y2;
	int points;
	
	points = 0;
	y2 = 0;
	while (y2 < status->trow)
	{
		x2 = 0;
		while(x2 < status->tcol)
		{
			if (status->token[y2][x2] == '*')
			{
				if (status->map[y1 + y2][x1 + x2] == '.')
					points += status->heatmap[y1 + y2][x1 + x2];
			}
			x2++;
		}
		y2++;
	}
	return (points);
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
	int points;

	y = 0;
	points = 0;
	moves = NULL;
	while (y + status->trow < status->row + 1)
	{
		x = 0;
		while (x + status->tcol < status->col + 1)
		{
			if(valid_field(x, y, status))
			{
				points = find_points(x, y, status);
				moves = store_move(x, y, points, moves);
			}
			x++;
		}
		y++;
	}
	return (moves);
}

/*
**	First initialization of variables in t_filler *status.
*/

void	set_status(t_filler *status)
{
	status->centerX = 0;
	status->centerY = 0;
	status->totalenemies = 0;
}


/*
** 	Free or reset particular variables for next turn
**		free map
**		free token
**		free heatmap
*/

void	reset_status(t_filler *status)
{
	
	ft_free2darray((void **) status->map, status->row);
	ft_free2darray((void **) status->token, status->trow);
	ft_free2darray((void **) status->heatmap, status->row);
	status->centerX = 0;
	status->centerY = 0;
	status->totalenemies = 0;
}

/*
** ingame is where the juiciness occurs.
** The game is initialized and the algorithm will begin searching for moves
** There is also logic to check whether there are any more moves left
** Once the possible moves are discovered the algorithm will have to choose the best one.
**
**	1. Discovery for moves.
**	2. Decide best move.
*/

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
	find_lowest(cursor);
	print_lowest(cursor);
	//print2dintarray(status->heatmap, status->row, status->col);
	/*
	while (cursor != NULL)
	{
		printf("%d, %d   points -> %d\n", cursor->y, cursor->x, cursor->points);
		cursor = cursor->next;
	}
	*/
	reset_status(status);
	free_moves(status);
	return (0);
}

int main()
{
	t_filler *status;

	status = malloc(sizeof(t_filler));
	set_player(status);
	set_status(status);
	while(in_game(status));
	return (0);
}
