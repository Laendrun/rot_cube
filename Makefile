NAME = rot_cube
SRC = $(addprefix src/, main.c)
MAT_SRC = $(addprefix mat/, mat.c)
OBJ := $(SRC:%.c=%.o)
MAT_OBJ := $(MAT_SRC:%.c=%.o)

CCFLAGS = -Wextra -Wall -Werror

all: $(NAME)

# MacOs
$(NAME): $(OBJ) $(MAT_OBJ)
	gcc $(CCFLAGS) $^ -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# MacOs
%.o: %.c
	gcc $(CCFLAGS) -Imlx -Iincludes -c $< -o $@

clean:
	rm -f $(OBJ) $(MAT_OBJ)

fclean: clean
	make clean -C mlx/
	rm -f $(NAME)

mlx:
	@$(MAKE) re -C mlx/

re: fclean all

.PHONY: mlx