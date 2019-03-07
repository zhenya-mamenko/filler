# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/11 13:54:51 by emamenko          #+#    #+#              #
#    Updated: 2019/03/07 00:54:47 by emamenko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:		$(NAME) all clean fclean re

NAME	=	emamenko.filler
SOURCES	=	filler.c get_next_line/get_next_line.c
LIBFT	=	get_next_line/libft

all:		$(NAME)

$(NAME):
			make -C $(LIBFT)
			gcc -o $(NAME) -Wall -Wextra -Werror -I. -L$(LIBFT) -lft $(SOURCES)

clean:
			make -C $(LIBFT) clean

fclean:		clean
			make -C $(LIBFT) fclean
			rm -f $(NAME)

re: 		fclean all
			make -C $(LIBFT) re

reclean:	re
			make -C $(LIBFT) reclean
