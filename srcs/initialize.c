/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 09:25:14 by ssong             #+#    #+#             */
/*   Updated: 2018/11/08 21:58:44 by ssong            ###   ########.fr       */
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

/*
** The corresponding player number is sent to the corresponding player,
** so all I need to do is search if I am player 1. If I am then I am character
** 'o', and if not then I am 'x'. I am also setting it for my opponent.
*/

void	set_player(t_filler *status)
{
	char *line;

	line = 0;
	if(!get_next_line(STDIN_FILENO, &line))
		exit(0);
	status->me = (line[10] == '1' ? 'O' : 'X');
	status->enemy = (line[10] == '1' ? 'X' :'O');
	free(line);
}

/*
**	The string that is given to me which gives dimensions of the map is
**  ex. "Plateau 14 30:". I am searching for the first whitespace then
**  using atoi to extract number then again searching for whitespace then
**  using atoi to extract the number.
*/

void	read_map_size(t_filler *status)
{
	char *line;
	char *place;

	line = 0;
	place = line;
	if(!get_next_line(STDIN_FILENO, &line))
		exit(0);
	line = ft_strchr(line, ' ');
	status->row = ft_atoi(line);
	line = ft_strchr(line + 1, ' ');
	status->col = ft_atoi(line);
	free(place);
}

/*
** Create a 2 dimensional char array according the dimensions provided.
** It will get_next_line the same number of times there are rows. Then 
** the program simply strdup's the map given to me with "+4" to dodge the
** first unnecessary characters.
*/


void	read_map(t_filler *status)
{
	int i;
	char *line;

	line = 0;
	i = 0;
	get_next_line(STDIN_FILENO, &line);
	free(line);
	status->map = malloc(sizeof(char *) * status->row + 1);
	while (i < status->row)
	{
		get_next_line(STDIN_FILENO, &line);
		status->map[i] = ft_strdup(line + 4);
		free(line);
		i++;
	}
	status->map[i] = NULL;
}


/*
**  Read dimensions of token and then create a copy
*/

void	read_token(t_filler *status)
{
	char *line;
	int i;

	i = 0;
	line = 0;
	get_next_line(STDIN_FILENO, &line);
	status->trow = ft_atoi(line + 6);
	status->tcol = ft_atoi(strchr(line + 7, ' '));
	free(line);
	status->token = malloc(sizeof(char *) * status->trow + 1);
	while (i < status->trow)
	{
		get_next_line(STDIN_FILENO, &line);
		status->token[i] = ft_strdup(line);
		free(line);
		i++;
	}
	status->token[i] = NULL;
}

void	find_centerofGravity_X(t_filler *status)
{
	int y;
	int x;
	int sumY;
	int sumX;

	sumY = 0;
	sumX = 0;
	y = 0;
	while (y < status->row)
	{
		x = 0;
		while (x < status->col)
		{
			if (status->map[y][x] == status->enemy)
			{
				sum += y;
				total++;
			}
			x++;
		}
		y++;
	}
}

void	find_centerofGravity_Y(t_filler *status)
{


}

void	find_centerofGravity(t_filler *status)
{
	find_centerofGravity_Y(status);
	find_centerofGravity_X(status);
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


/*
**  Main Function that holds all the reading functions
*/

void	initialize_game(t_filler *status)
{	
	read_map_size(status);
	read_map(status);
	read_token(status);
	find_centerofGravity(status);
	generate_heatmap(status);
}
