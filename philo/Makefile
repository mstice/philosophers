CYAN := \033[0;96m
MAGENTA := \033[0;95m
YELLOW := \033[0;93m
GREEN := \033[0;92m
RED := \033[0;91m
RESET := \033[0m

NAME := philo

SRC_DIR := src
OBJ_DIR := obj

SRC := $(SRC_DIR)/main.c \
	   $(SRC_DIR)/init_utils.c \
	   $(SRC_DIR)/input_check.c \
	   $(SRC_DIR)/routines.c \
	   $(SRC_DIR)/routine_utils.c \
	   $(SRC_DIR)/utils.c \
	   $(SRC_DIR)/time_utils.c \
	   $(SRC_DIR)/free_utils.c 

OBJ := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC:.c=.o))
INCLUDE := inc

CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread -g3 -I$(INCLUDE) #-fsanitize=thread

RM := rm -rf

$(NAME): $(OBJ)
		@$(CC) $(CFLAGS) $^ -o $(NAME)
		@echo "\n${GREEN} Created $(NAME)${RESET}\n"

$(OBJ): $(OBJ_DIR)%.o:$(SRC_DIR)%.c
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(CFLAGS) -c -o $@ $^
		@echo "${MAGENTA} ~ Compiled -> ${CYAN} $< ${RESET}"

all: $(NAME)

clean:
		@$(RM) $(OBJ) $(OBJ_DIR)
		@echo "${RED} Cleaned $(OBJ_DIR) directory${RESET}"

fclean: clean
	@$(RM) $(NAME)
	@echo "${RED} Cleaned $(NAME) library${RESET}"

re: fclean all

.PHONY: all clean fclean re
