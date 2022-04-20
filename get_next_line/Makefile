# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/17 11:19:27 by mpeharpr          #+#    #+#              #
#    Updated: 2022/04/20 11:19:17 by mpeharpr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a

HEADER = get_next_line.h
SRCS = get_next_line_utils.c get_next_line.c
OBJS = $(SRCS:.c=.o)

$(NAME):
	gcc -Wall -Wextra -Werror -c $(SRCS) -D BUFFER_SIZE=1000
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
