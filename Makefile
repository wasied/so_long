NAME	=	so_long
CC	=	gcc
FLAGS	=	-Wall -Wextra -Werror

MLX		=	mlx
SRC		=	src/main.c src/surface.c src/map.c src/utils.c src/player.c src/math.c src/extra.c \
			get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
			ft_printf/ft_printf.c ft_printf/ft_putnbr_base.c ft_printf/ft_types.c ft_printf/ft_utils.c
OBJ		=	$(SRC:.c=.o)

%.o: %.c
	$(CC) $(FLAGS) -D BUFFER_SIZE=1000 -I$(MLX) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -L$(MLX) -l$(MLX) -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ)


fclean: clean
	rm -f $(NAME)

re: fclean all
