NAME = fdf
FLAGS = -Wall -Wextra -Werror -I./
SRC = main.c read.c error.c events.c draw.c projections.c helpers.c \
		help.c color.c events2.c
LIBFT = libft/
MINILIBX = minilibx/

OBJ = $(SRC:.c=.o)

%.o: %.c
	gcc -c -o $@ $< $(FLAGS)

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT)
	make -C $(MINILIBX)
	gcc $(OBJ) -o $(NAME) -L libft -lft -L minilibx -lmlx -framework OpenGL -framework AppKit

clean:
	rm -f $(OBJ)
	make -C $(LIBFT) clean
	make -C $(MINILIBX) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT) fclean
	make -C $(MINILIBX) clean

re:	fclean all


build:
	rm -f $(OBJ)
	rm -f $(NAME)
	gcc $(FLAGS) -c $(SRC) -g
	gcc $(OBJ) -o $(NAME) -L libft -lft -L minilibx -lmlx -framework OpenGL -framework AppKit
