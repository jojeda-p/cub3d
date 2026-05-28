NAME = cub3d
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I include -I minilibx-linux
MLX_DIR = minilibx-linux
MLX_LIB = -L$(MLX_DIR) -lmlx -lXext -lX11
SRC_DIR = srcs
OBJ_DIR = objects
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_LIB)

$(MLX_DIR)/libmlx.a:
	@if [ ! -d $(MLX_DIR) ]; then \
		echo "Error: MiniLibX directory '$(MLX_DIR)' not found."; \
		echo "Please clone or copy MiniLibX into '$(MLX_DIR)' and re-run make."; \
		exit 1; \
	fi
	@$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re


