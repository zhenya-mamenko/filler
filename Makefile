# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/11 13:54:51 by emamenko          #+#    #+#              #
#    Updated: 2019/03/09 17:47:29 by emamenko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:		$(NAME) all clean fclean re

NAME	=	emamenko.filler
SOURCES	=	filler.c helpers.c shape.c hitmap.c place.c board.c \
			get_next_line/get_next_line.c
LIBFT	=	get_next_line/libft

all:		$(NAME)

$(NAME):
			make -C $(LIBFT)
			gcc -o $(NAME) -Wall -Wextra -Werror -I. -L$(LIBFT) -lft $(SOURCES)
			cp $(NAME) resources/players

clean:
			make -C $(LIBFT) clean

fclean:		clean
			make -C $(LIBFT) fclean
			rm -f $(NAME)

re: 		fclean all
			make -C $(LIBFT) re

reclean:	re
			make -C $(LIBFT) reclean
