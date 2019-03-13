/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 09:25:14 by ssong             #+#    #+#             */
/*   Updated: 2018/12/11 13:29:16 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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
	if(!get_next_filler(STDIN_FILENO, &line))
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
	if(!get_next_filler(STDIN_FILENO, &line))
		exit(0);
	free(line);
	status->map = malloc(sizeof(char *) * status->row + 1);
	while (i < status->row)
	{
		if (!get_next_filler(STDIN_FILENO, &line))
			exit(0);
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
	if(!get_next_filler(STDIN_FILENO, &line))
		exit(0);
	status->trow = ft_atoi(line + 6);
	status->tcol = ft_atoi(strchr(line + 7, ' '));
	free(line);
	status->token = malloc(sizeof(char *) * status->trow + 1);
	while (i < status->trow)
	{
		if(!get_next_filler(STDIN_FILENO, &line))
			exit(0);
		status->token[i] = ft_strdup(line);
		free(line);
		i++;
	}
	status->token[i] = NULL;
}



/*
**  Main Function that holds all the reading functions and decides destination based on 
** 	the stage of the game and what player number I am.
*/

void	initialize_game(t_filler *status)
{	
	read_map_size(status);
	read_map(status);
	read_token(status);
	find_origin(status);
	if (status->me == 'O')
	{
		set_stage(status);
		set_destination(status);
	}
	else
	{
		set_stage2(status);
		set_destination2(status);
	}
	generate_heatmap(status);
}
