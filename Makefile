NAME	=	so_long
CC		=	gcc
# FLAGS	=	-Wall -Wextra -Werror

MLX		=	mlx
SRC		=	src/main.c src/surface.c src/map.c src/utils.c src/player.c src/math.c \
			get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

# SRC		=	src_old/map.c src_old/player.c src_old/so_long.c src_old/utils.c src_old/window.c \
			# get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJ		=	$(SRC:.c=.o)

%.o: %.c
	$(CC) $(FLAGS) -D BUFFER_SIZE=1000 -I$(MLX) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -L$(MLX) -l$(MLX) -framework OpenGL -framework AppKit -o $(NAME)