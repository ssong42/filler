/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:28:49 by ssong             #+#    #+#             */
/*   Updated: 2018/12/13 15:29:00 by ssong            ###   ########.fr       */
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
