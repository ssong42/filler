/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 09:25:14 by ssong             #+#    #+#             */
/*   Updated: 2018/11/10 15:23:35 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"


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
