/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 20:50:36 by ssong             #+#    #+#             */
/*   Updated: 2018/11/07 09:54:30 by ssong            ###   ########.fr       */
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
}				t_filler;

typedef	struct	s_moves
{
	int x;
	int y;
	int	distance;
	struct s_moves *next;
}				t_moves;

void	read_map_size(t_filler *status);
void	set_player(t_filler *status);
void	initialize_game(t_filler *status);
int		in_game(t_filler *status);
void	print2darray(char **map);

#endif
