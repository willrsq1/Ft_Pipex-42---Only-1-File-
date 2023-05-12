
### COMPILATION ###
CC      = gcc
FLAGS  = -Wall -Wextra -Werror -g 

### EXECUTABLE ###
NAME   = pipex

### INCLUDES ###
OBJ_PATH  = .
HEADER = .
SRC_PATH  = .

### SOURCE FILES ###

SOURCES =		ft_pipex.c

### OBJECTS ###

SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))


### COLORS ###
NOC         = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLACK       = \033[1;30m
RED         = \033[1;31m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
VIOLET      = \033[1;35m
CYAN        = \033[1;36m
WHITE       = \033[1;37m

### RULES ###

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^
	@echo "$(GREEN)Project successfully compiled"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)/*.h
	@$(CC) $(FLAGS) -c -o $@ $<
	@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(NOC)"

clean:
	@echo "$(GREEN)Supressing libraries files$(CYAN)"
	@rm -f $(OBJ_PATH)/*.o

fclean:
	@echo "$(GREEN)Supressing libraries files$(CYAN)"
	@rm -f $(OBJ_PATH)/*.o
	@rm -f $(NAME)

norminette:
	@norminette

re: fclean
	@$(MAKE) all

.PHONY: re fclean clean norminette
