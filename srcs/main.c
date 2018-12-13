/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 20:42:56 by ssong             #+#    #+#             */
/*   Updated: 2018/12/10 21:00:20 by ssong            ###   ########.fr       */
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

typedef struct s_temp
{
	int x2;
	int y2;
	int matches;
	char loc;

}	t_temp;

bool		valid_field(int x1, int y1, t_filler *status)
{
	t_temp temp;

	temp.matches = 0;
	temp.y2 = -1;
	while (++temp.y2 < status->trow)
	{
		temp.x2 = -1;
		while(++temp.x2 < status->tcol)
		{
			if (status->token[temp.y2][temp.x2] == '*')
			{
				if (y1 + temp.y2 < 0 || y1 + temp.y2 >= status->row ||
				x1 + temp.x2 < 0 || x1 + temp.x2 >= status->col)
					return (0);
				temp.loc = status->map[y1 + temp.y2][x1 + temp.x2];
				if (temp.loc == status->me || temp.loc == status->me + 32)
					temp.matches++;
				if (temp.loc == status->enemy || temp.loc ==  status->enemy + 32)
					return (0);
			}
		}
	}
	return ((temp.matches == 1) ? 1 : 0);
}

/*
**		check if the y and x position is equal to a '*' if it is then, 
**	
**
*/

bool	valid_field1(int x1, int y1, t_filler *status)
{
	int x2;
	int y2;
	int matches;
	char loc;

	matches = 0;
	y2 = -1;
	while (++y2 < status->trow)
	{
		x2 = -1;
		while(++x2 < status->tcol)
		{
			if (status->token[y2][x2] == '*')
			{
				loc = status->map[y1 + y2][x1 + x2];
				if (loc == status->me || loc == status->me + 32)
					matches++;
				if (matches > 1 || loc == status->enemy || loc ==  status->enemy + 32)
					return (0);
			}
		}
	}
	if (matches == 0)
		return (0);
	return (1);
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

	y = (status->trow - 1) * -1;
	points = 0;
	moves = NULL;
	while (y < status->row)
	{
		x = (status->tcol - 1) * -1;
		while (x < status->col)
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
	status->x2 = 0;
	status->y2 = 0;
	status->totalenemies = 0;
	status->stage = 0;
	status->init = 0;
	status->initx = 0;
	status->inity = 0;
	status->initex = 0;
	status->initey = 0;
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
	status->x2 = 0;
	status->y2 = 0;
	status->totalenemies = 0;
}

/*
**	Find lowest points out of all moves
*/

t_moves	*find_lowest(t_moves *moves)
{
	t_moves *cursor;
	t_moves *min;

	cursor = moves;
	min = moves;
	while (cursor != 0)
	{
		if (cursor->points < min->points)
			min = cursor;
		cursor = cursor->next;	
	}
	return (min);
}

/*
**	Print the coordinates of the move
*/

void	print_move(t_moves *moves)
{
	ft_printf("%d %d\n", moves->y, moves->x);	
}

/*
**	Free moves linked list
*/

void	free_moves(t_moves *moves)
{
	t_moves *cursor;
	t_moves *next;

	cursor = moves;
	while (cursor != NULL)
	{
		next = cursor->next;
		ft_memdel((void **)&cursor);
		cursor = next;
	}
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

	initialize_game(status);
	moves = find_moves(status);
	if (!moves)
	{
		ft_printf("%s\n", "no moves");
		return (0);
	}
	print_move(find_lowest(moves));
	reset_status(status);
	free_moves(moves);
	return (1);
}

int main()
{
	t_filler *status;

	status = malloc(sizeof(t_filler));
	set_status(status);
	set_player(status);
	while(in_game(status));
	return (0);
}
