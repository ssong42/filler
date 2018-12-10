/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 20:50:36 by ssong             #+#    #+#             */
/*   Updated: 2018/12/06 21:33:20 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"
#define BUF_SIZE 10

typedef	struct	s_filler
{
	char	me;
	char	enemy;
	char	**map;
	char	**token;
	int		**heatmap;
	int		row;
	int		col;
	int		trow;
	int		tcol;
	int		totaltoken;
	int	x2;
	int	y2;
	int	totalenemies;
	int	stage;
	int	init;
	int	initx;
	int	inity;
	int	initEx;
	int	initEy;
}				t_filler;

typedef	struct	s_moves
{
	int x;
	int y;
	int	points;
	struct s_moves *next;
}				t_moves;

/*
**	initialize.c
*/

void	read_map_size(t_filler *status);

/*
**	main.c
*/

void	set_player(t_filler *status);
void	set_status(t_filler *status);
void	initialize_game(t_filler *status);
int		in_game(t_filler *status);

/*
**	heatmap.c
*/

void	find_centerofGravity(t_filler *status);
void	assign_heatvalue(int y1, int x1, t_filler *status);
void	generate_heatmap(t_filler *status);

/*
**	debug.c
*/

void	print2darray(char **map);
void	print2dintarray(int **map, int r, int c);

#endif
