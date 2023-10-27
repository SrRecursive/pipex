# ========================================================================== #

# <-- Color Library --> #

# <-- Text Color --> #
T_BLACK = \033[30m
T_RED = \033[31m
T_GREEN = \033[32m
T_YELLOW = \033[33m
T_BLUE = \033[34m
T_MAGENTA = \033[35m
T_CYAN = \033[36m
T_WHITE = \033[37m

# <-- Text Style --> #
BOLD = \033[1m
ITALIC = \033[2m
UNDERLINE = \033[3m
STRIKETHROUGH = \033[4m

# <-- Background Color --> #
B_BLACK = \033[40m
B_RED = \033[41m
B_GREEN = \033[42m
B_YELLOW = \033[43m
B_BLUE = \033[44m
B_MAGENTA = \033[45m
B_CYAN = \033[46m
B_WHITE = \033[47m

# <-- Reset Everything --> #
RESET = \033[0m

# ========================================================================== #

# <-- Library's Name --> #
NAME = pipex

# <-- Compilation Command --> #
CC = gcc

# <-- Compilation Flags --> #
CFLAGS = -Wall -Wextra -Werror

# <-- Remove Command -->#
RM = rm -f

# <-- Directories --> #
SRC_DIR = src/
UTILS_DIR = utils/

# <-- Files --> #
SRC_FILES = pipex.c
UTILS_FILES = error.c \
				execute.c \
				process.c

# <-- Directories + Files --> #
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
UTILS = $(addprefix $(UTILS_DIR), $(UTILS_FILES))

# <-- Objects --> #
OBJ_SRC = $(SRC:.c=.o)
OBJ_UTILS = $(UTILS:.c=.o)

# ========================================================================== #

# <-- Main Target --> #
all: $(NAME)

# <-- Compile Library --> #

# <--Library Creation-->#
$(NAME): $(OBJ_SRC) $(OBJ_UTILS)
	make -C libft
	@echo "$(B_GREEN)$(T_YELLOW)$(BOLD)Objects created successfully$(RESET)"
	$(CC) $(CFLAGS) $(OBJ_SRC) $(OBJ_UTILS) -Llibft -lft -o $(NAME)
	@echo "$(B_GREEN)$(T_YELLOW)$(BOLD)$(NAME) created successfully$(RESET)"

# <-- Objects Creation --> #
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# <-- Objects Destruction --> #
clean:
	@make clean -C libft
	$(RM) $(OBJ_SRC) $(OBJ_UTILS)
	@echo "$(B_RED)$(T_YELLOW)$(BOLD)Source Object destroyed successfully$(RESET)"

# <- Clean Execution + Library Destruction -> #
fclean: clean
	@make fclean -C libft
	$(RM) $(NAME)
	@echo "$(B_RED)$(T_YELLOW)$(BOLD)Library destroyed successfully$(RESET)"

# <- Fclean Execution + All Execution -> #
re: fclean all

# <- Targets Declaration -> #
.PHONY = all clean fclean re

# ========================================================================== #
