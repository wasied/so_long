# so_long - A simple 2D game
# Use this makefile to compile to game

# Compile informations
NAME		=	so_long
SANIFLAG	=	-fsanitize=address -g
FLAGS		=	-Wall -Wextra -Werror $(SANIFLAG)

# This works only when mlx is loaded into the env (on school computers)
MLX_INCLUDE =	-lmlx -framework OpenGL -framework AppKit

# This is all the source files we want to compile
SRC_FOLDER	=	src/
SRC_FILES	=	extra.c main.c map.c player.c surface.c utils.c
OBJS		=	$(addprefix $(SRC_FOLDER), $(SRC_FILES:%.c=%.o))

# This is other projects we want to include to our source files
GNL_PATH	=	get_next_line/
GNL_LIB		= 	$(GNL_PATH)get_next_line.a
PRINTF_PATH =	ft_printf/
PRINTF_LIB	=	$(PRINTF_PATH)libftprintf.a

# Our compile rules
%.o: %.c
	gcc $(FLAGS) -c $< -o $@

$(NAME): 	$(OBJS)
	make -C $(GNL_PATH)
	make -C $(PRINTF_PATH)
	gcc $(FLAGS) $(OBJS) $(GNL_LIB) $(PRINTF_LIB) $(MLX_INCLUDE) -o $(NAME)

# Here are mandatory rules
all:		$(NAME)

clean:
	rm -rf $(OBJS)
	make clean -C $(GNL_PATH)
	make clean -C $(PRINTF_PATH)

fclean:		clean
	rm -f $(NAME)
	make fclean -C $(GNL_PATH)
	make fclean -C $(PRINTF_PATH)

re:			fclean all

.PHONY:		all clean fclean re