SRC_FOLDER = 	./src

SRC = 			main.c \
				matrices.c \
				matrices2.c \
				matrices3.c \
				matrices4.c \
				vec_operations.c \
				vec_operations2.c \
				vec_operations3.c \
				ray.c \
				sphere.c \
				intersection.c \
				materials.c \
				macro_subs.c \
				macro_subs2.c \
				light.c \
				utils.c \
				world.c \
				world2.c \
				camera.c \
				shadow.c \
				hits.c \
				planes.c \
				cylinder.c \
				parsing.c \
				parse_utils.c

OBJ_FOLDER = 	obj

OBJ = 			$(patsubst %.c,$(OBJ_FOLDER)/%.o,$(SRC))

LIBFT =			./libft
LIBMLX =		./minilibx-linux

CC =			gcc
FLAGS =			-g -Wall -Wextra -Werror -o3
INC =			./inc

NAME =			miniRT

all: $(NAME)
	# ./miniRT

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) libft.a libmlx_Linux.a -I/minilibx-linux -lXext -lX11 -lm -lz

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c | $(OBJ_FOLDER)
	$(CC) $(FLAGS) -c -I$(INC) -I$(LIBMLX) $< -o $@

$(OBJ_FOLDER): libft
	mkdir -p $(OBJ_FOLDER)

libft:
	make -C $(LIBFT)
	cp $(LIBFT)/libft.a .
	make -C $(LIBMLX)
	cp $(LIBMLX)/libmlx_Linux.a .

clean:
	rm -rf $(OBJ_FOLDER)
	make clean -C $(LIBFT)
	make clean -C $(LIBMLX)

fclean: clean
	rm -f $(NAME)
	rm -rf libft.a
	rm -rf libmlx_Linux.a
	make fclean -C $(LIBFT)

re: fclean all

run: re
	./miniRT RT_files/prova.rt

.PHONY: all clean fclean re run libft