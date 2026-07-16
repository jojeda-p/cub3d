# ============================================================================ #
#                                 MAKEFILE RAÍZ                                #
#         Delega la compilación en Mandatory/ (make) y Bonus/ (make bonus)     #
# ============================================================================ #

MANDATORY_DIR = Mandatory
BONUS_DIR     = Bonus

# ============================================================================ #
#                                  COLORES                                     #
# ============================================================================ #

DEF_COLOR   = \033[0;39m
RED         = \033[0;91m
GREEN       = \033[0;92m
YELLOW      = \033[0;93m
CYAN        = \033[0;96m

# ============================================================================ #
#                                   REGLAS                                     #
# ============================================================================ #

# make -> compila SOLO la parte mandatory (comportamiento por defecto)
all:
	@echo "$(CYAN)==> Compilando parte MANDATORY...$(DEF_COLOR)"
	@$(MAKE) --no-print-directory -C $(MANDATORY_DIR)

# make bonus -> compila SOLO la parte bonus
bonus:
	@echo "$(CYAN)==> Compilando parte BONUS...$(DEF_COLOR)"
	@$(MAKE) --no-print-directory -C $(BONUS_DIR)

# make clean -> limpia objetos de AMBAS partes (si existen)
clean:
	@$(MAKE) --no-print-directory -C $(MANDATORY_DIR) clean
	@$(MAKE) --no-print-directory -C $(BONUS_DIR) clean

# make fclean -> limpia objetos + ejecutables de AMBAS partes
fclean:
	@$(MAKE) --no-print-directory -C $(MANDATORY_DIR) fclean
	@$(MAKE) --no-print-directory -C $(BONUS_DIR) fclean

# make re -> recompila mandatory (comportamiento por defecto, igual que "all")
re: fclean all

# make re_bonus -> recompila bonus
re_bonus:
	@$(MAKE) --no-print-directory -C $(BONUS_DIR) fclean
	@$(MAKE) --no-print-directory -C $(BONUS_DIR)

.PHONY: all bonus clean fclean re re_bonus