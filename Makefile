# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

NAME = rot_cube
SRC = $(addprefix src/, main.c \
						inputs.c \
						draw.c \
						draw_utils.c \
						utils.c \
						init.c \
						update.c \
								)
MAT_SRC = $(addprefix mat/, mat.c)
OBJ := $(SRC:%.c=%.o)
MAT_OBJ := $(MAT_SRC:%.c=%.o)

CCFLAGS =

all: $(NAME)

# MacOs
$(NAME): $(OBJ) $(MAT_OBJ)
	gcc $(CCFLAGS) $^ -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"

debug: $(OBJ) $(MAT_OBJ)
	gcc $(CCFLAGS) $^ -fsanitize=address -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# MacOs
%.o: %.c
	@echo "$(CYAN)Compiling mlx$(DEF_COLOR)"
	make -C mlx/
	gcc $(CCFLAGS) -Imlx -Iincludes -c $< -o $@

clean:
	rm -f $(OBJ) $(MAT_OBJ)

fclean: clean
	make fclean -C mlx/
	rm -f $(NAME)

mlx:
	@$(MAKE) re -C mlx/

re: fclean all

.PHONY: mlx