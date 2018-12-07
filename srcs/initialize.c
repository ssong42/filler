/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 09:25:14 by ssong             #+#    #+#             */
/*   Updated: 2018/12/07 13:18:39 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	get_next_filler(int fd, char **line)
{
	char	buffer[2];
	char 	*temp;
	int	br;

	temp = malloc(1);
	temp = 0;
	if (fd < 0 || read(fd, buffer, 0) < 0)
		return (-1);
	while((br = read(fd, buffer, 1)) && buffer[0] != '\n')
	{
		buffer[br] = 0;
		temp = ft_strjoinfreee(temp, buffer);
	}
	*line = temp;
	if (br == 0)
		return (0);
	return (1);
}

/*
** For precausionary measure, I need to check if there are second player. If there 
** is it can mess up the spacing when I read in the other variables.
*/

int	check_second_player()
{
	char	buffer[2];
	char	*line;

	if (read(STDIN_FILENO, buffer, 0) < 0)
		return (-1);
	read(STDIN_FILENO, buffer, 1);
	if (buffer[0] == '$')
	{
		get_next_filler(STDIN_FILENO, &line);
		free (line);
	}
	return (1);
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
	if (!ft_strcmp(line + 17, "ssong.filler]"))
	{
		status->me = 'O';
		status->enemy = 'X';
	}
	else
	{
		status->me = 'X';
		status->enemy = 'O';
	}
	check_second_player();
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
					status->initEx = x1;
					status->initEy = y1;
				}
			}
		}
		status->init = 1;
	}
}

/*
**  Depending on the status check if the mission is complete.
**  If stage = 0, then I need to find the initial point and find the y and x directly
**	across.
** 	Depending on stage define the COG location 
*/

/*
void	check_stage(status)
{
	//see if I have a piece touching left wall.
	//	if so then I need to set status to 1.
	//see if I have a piece touching right wall.
	//	if so then I need to set status to 2.
	//see if I have met both conditions now go towards enemy.
}
*/

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

/*
**	Assign to corner from a specific point on a map.
*/

void	AssignCorner(t_filler *status)
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
	else if (status->stage == 5)
	{
		status->y2 = 0;
		status->x2 = 0;
	}
	else
	{
		status->stage = 1;
		find_centerofGravity(status);
	}
	status->stage++;
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
		status->y2 = status->row / 3;
	}
	else if (status->stage >= 2)
	{
		AssignCorner(status);
	}
}

/*
**  Main Function that holds all the reading functions
*/

void	initialize_game(t_filler *status)
{	
	read_map_size(status);
	read_map(status);
	read_token(status);
	find_origin(status);
	set_stage(status);
	set_destination(status);
	generate_heatmap(status);
}
