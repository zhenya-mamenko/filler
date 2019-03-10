# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/11 13:54:51 by emamenko          #+#    #+#              #
#    Updated: 2019/03/10 12:01:41 by emamenko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:		$(NAME) all clean fclean re

NAME	=	emamenko.filler
SOURCES	=	filler.c helpers.c shape.c hitmap.c place.c board.c token.c \
			get_next_line/get_next_line.c
LIBFT	=	get_next_line/libft

all:		$(NAME)

$(NAME):
			make -C $(LIBFT)
			gcc -o $(NAME) -Wall -Wextra -Werror $(SOURCES) -I. -L$(LIBFT) -lft

clean:
			make -C $(LIBFT) clean

fclean:		clean
			make -C $(LIBFT) fclean
			rm -f $(NAME)

re: 		fclean all
			make -C $(LIBFT) re

reclean:	re
			make -C $(LIBFT) reclean
