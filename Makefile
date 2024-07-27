NAME		=	so_long

CC			=	gcc

FLAG		=	-Wall -Wextra -Werror -g3

LIBFT_PATH	=	./libft/

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

MLX_FILE	=	libmlx.a

MLX_FLAG	=	-lX11 -lXext

MLX_PATH	=	./minilibx-linux/

MLX_LIB		=	$(addprefix $(MLX_PATH), $(MLX_FILE))

MLX_CLONE	=	https://github.com/42Paris/minilibx-linux.git

MLX_EX		=	$(MLX_LIB) $(MLX_FLAG)

C_FILE		=	so_long.c 		\
				init.c 			\
				so_long_utils.c \
				map.c 			\
				move.c			\
				exit_free.c		\
				check_map.c		\
				check_path.c

SRC_DIR		=	./srcs/

SRC			=	$(addprefix $(SRC_DIR),$(C_FILE))

OBJ			=	$(SRC:.c=.o)

.c.o:
	@$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

lib:
	@echo "\033[0;33mCOMPILING $(LIBFT_PATH)\n"
	@make -sC $(LIBFT_PATH)
	@echo "\033[1;32mlibft.a created\n"

mlx:
	@echo "\033[0;33mCLONING $(MLX_CLONE)...\n"
	@if [ ! -d "$(MLX_PATH)" ]; then \
		git clone -q $(MLX_CLONE); \
		echo "\033[1;32m$(MLX_PATH) created"; \
	else \
		echo "\033[1;32mRepository already exists."; \
	fi
	@echo "\033[0;33m\nCOMPILING $(MLX_PATH)...\n"
	@make -sC $(MLX_PATH)
	@echo "\033[1;32m\nMLX_lib created"

$(NAME): lib mlx $(OBJ)
	@echo "\033[0;33m\nCOMPILING SO_LONG...\n"
	@$(CC) $(OBJ) $(LIBFT_LIB) $(MLX_EX) -o $(NAME)
	@echo "\033[1;32m./so_long created\n"

clean:
	@echo "\033[0;31m\nDeleting Obj file in $(LIBFT_PATH)...\n"
	@make clean -sC $(LIBFT_PATH)
	@echo "\033[1;32mDone\n"
	@echo "\033[0;31mDeleting So_long object...\n"
	@rm -f $(OBJ)
	@echo "\033[1;32mDone\n"
	@echo "\033[0;31mDeleting Obj file in $(MLX_PATH)...\n"
	@make clean -sC $(MLX_PATH)

fclean: clean
	@echo "\033[0;31m\nDeleting so_long executable...\n"
	@rm -f $(NAME)
	@make fclean -sC $(LIBFT_PATH)
	@echo "\033[1;32mDone\n"
	@echo "\033[0;31mDeleting $(MLX_PATH)...\n"
	@rm -rf $(MLX_PATH)

re: fclean all

norminette:
	norminette ./srcs/

.PHONY: all clean fclean re
