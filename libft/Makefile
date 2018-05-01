# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssong <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/26 18:30:33 by ssong             #+#    #+#              #
#    Updated: 2018/04/26 10:15:50 by ssong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
INCLUDES = ./includes/.
SRCSD = ./srcs/
PDIR = ./printffunctions/
FLAGS = -Wall -Werror -Wextra

FILES = ft_strrchr ft_putstr ft_strcmp ft_strlcat ft_memcpy \
		ft_memmove ft_strsplit ft_strncpy ft_lstmap \
		ft_lstadd ft_striter ft_strstr ft_isdigit ft_putnbr \
		ft_memccpy ft_strdel ft_memchr ft_bzero \
		ft_isalnum ft_putstr_fd ft_lstiter ft_lstdelone ft_toupper \
		ft_strcpy ft_lstnew ft_strdup ft_putnbr_fd ft_striteri \
		ft_strmap ft_putendl_fd ft_memdel ft_strnstr ft_putchar \
		ft_isascii ft_strlen ft_strsub ft_strnew ft_memalloc ft_putendl \
		ft_strncat ft_itoa ft_strncmp ft_memcmp ft_strtrim ft_strequ \
		ft_putchar_fd ft_memset ft_isalpha ft_strcat ft_tolower \
		ft_strnequ ft_strjoin ft_atoi ft_strclr ft_strmapi \
		ft_isprint ft_lstdel ft_strchr ft_btree_create_node \
		ft_countdigits ft_countwords ft_free2darray ft_iswhite \
		ft_mem_grid ft_straddchr ft_strjoinfree ft_uintmaxt_itoa \
		ft_hexitoa ft_hex_countdigits ft_hex_itoa ft_itoa_base \
		ft_countdigits_base ft_itoa_deci ft_itoa_float \
		ft_intmaxt_itoa ft_strrcpy ft_strcatnew ft_wstrdup \
		ft_wputstr ft_wputchar ft_extractstring get_next_line \
		ft_twodchararray

PFILES = ft_printf print_decimal print_string print_hexi print_octal \
		 print_udecimal print_address print_printed print_wstring \
		 setinfo set_flag_info parse_flags print_char args_modifiers

CFILES = $(patsubst %, $(SRCSD)%.c, $(FILES)) $(patsubst %, $(PDIR)%.c, $(PFILES))
OFILES = $(patsubst %, %.o, $(FILES)) $(patsubst %, %.o, $(PFILES))

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) -c $(CFILES) -I $(INCLUDES)
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME)

clean:
	@rm -rf $(OFILES)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
