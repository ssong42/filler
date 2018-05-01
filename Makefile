# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssong <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/29 14:40:44 by ssong             #+#    #+#              #
#    Updated: 2018/04/26 09:39:39 by ssong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ssong.filler
INCLUDES = ./includes/
SRCSD = ./srcs/
LIB = ./libft/libftprintf.a
LIBINCLUDES = libft/includes/
PDIR = ./printffunctions/
FLAGS = -Wall -Werror -Wextra
FILES = main initialize

CFILES = $(patsubst %, $(SRCSD)%.c, $(FILES))



#OPPONENTS
RESRCS = ./resources/players/
MAPS = /maps



all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(LIB) $(CFILES) -I $(INCLUDES) -o $(NAME) -I $(LIBINCLUDES)

play:
	./resources/filler_vm -p1 ./$(NAME) -f ./resources/maps/map00

versus:
	./resources/filler_vm -p1 ./$(NAME) -p2 $(RESRCS)hcao.filler  -v -f ./resources/maps/map00

comp:
	./resources/filler_vm -p1 $(RESRCS)grati.filler -p2 $(RESRCS)hcao.filler -v -f ./resources/maps/map00

clean:
	rm -rf $(NAME)

re: clean all
