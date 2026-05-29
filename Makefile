# ============================================================================ #
#                                 VARIABLES                                    #
# ============================================================================ #

NAME        = cub3d

CC          = cc
RM          = rm -f

CFLAGS      = -Wall -Wextra -Werror -I include -I minilibx-linux
DEPFLAGS    = -MMD -MP

SRC_DIR     = srcs
OBJ_DIR     = objects
INC_DIR     = include

# ============================================================================ #
#                            MINILIBX (linux)                                  #
# ============================================================================ #

MLX_DIR     = include/minilibx-linux
MLX_LIB     = -L$(MLX_DIR) -lmlx -lXext -lX11

INCLUDES    = -I$(INC_DIR) -I$(MLX_DIR)
LIBS        = $(MLX_LIB)

# ============================================================================ #
#                                 SOURCES                                     #
# ============================================================================ #
# Norma: todos los .c deben estar listados explícitamente (sin wildcard)

SRC_FILES   =	main.c \
				utils/utils.c \
				render/map.c \
				parse/parse.c \
				input/input.c \
				init/init.c \
				init/window.c


SRCS        = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
DEPS        = $(OBJS:.o=.d)

# ============================================================================ #
#                                  COLORES                                     #
# ============================================================================ #

DEF_COLOR   = \033[0;39m
GRAY        = \033[0;90m
RED         = \033[0;91m
GREEN       = \033[0;92m
YELLOW      = \033[0;93m
BLUE        = \033[0;94m
MAGENTA     = \033[0;95m
CYAN        = \033[0;96m
WHITE       = \033[0;97m

# ============================================================================ #
#                                   REGLAS                                     #
# ============================================================================ #

all: $(NAME)

$(NAME): $(OBJS) $(MLX_DIR)/libmlx.a
	@echo "$(YELLOW)Enlazando objetos...$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@echo "$(GREEN)✨ Cub3d compilado con éxito! ✨$(DEF_COLOR)"
	@$(call PRINT_ASCII_ART)

# Compila MLX automáticamente (y falla con mensaje si no existe la carpeta)
$(MLX_DIR)/libmlx.a:
	@if [ ! -d $(MLX_DIR) ]; then \
		echo "$(RED)Error: MiniLibX directory '$(MLX_DIR)' not found.$(DEF_COLOR)"; \
		echo "$(YELLOW)Clona o copia MiniLibX dentro de '$(MLX_DIR)' y vuelve a ejecutar make.$(DEF_COLOR)"; \
		exit 1; \
	fi
	@echo "$(MAGENTA)Compilando MiniLibX...$(DEF_COLOR)"
	@$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(CYAN)Compilando: $(GRAY)$<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Limpiando archivos objeto...$(DEF_COLOR)"
	@$(RM) $(OBJS) $(DEPS)

fclean: clean
	@echo "$(RED)Eliminando ejecutable...$(DEF_COLOR)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)

# ============================================================================ #
#                                 ASCII ART                                    #
# ============================================================================ #

define PRINT_ASCII_ART
echo "$(BLUE)"
echo " ▄████████ ███    █▄  ▀█████████▄   ▄██████▄  ████████▄  "
echo "███    ███ ███    ███   ███    ███ ██      ██ ███   ▀███ "
echo "███    █▀  ███    ███   ███    ███         ██ ███    ███ "
echo "███        ███    ███  ▄███▄▄▄██▀      ▄███▀  ███    ███ "
echo "███        ███    ███ ▀▀███▀▀▀██▄         ▀█▄ ███    ███ "
echo "███    █▄  ███    ███   ███    ██▄ ██      ██ ███    ███ "
echo "███    ███ ███    ███   ███    ███ ██      ██ ███   ▄███ "
echo "████████▀  ████████▀  ▄█████████▀   ▀██████▀  ████████▀  "
echo ""
echo "$(DEF_COLOR)"
endef