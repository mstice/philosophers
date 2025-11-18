CYAN=$(shell echo -e "\033[0;96m")
MAGENTA=$(shell echo -e "\033[0;95m")
YELLOW=$(shell echo -e "\033[0;93m")
GREEN=$(shell echo -e "\033[0;92m")
RED=$(shell echo -e "\033[0;91m")
RESET=$(shell echo -e "\033[0m")

NAME := philo_bonus

SRC_DIR := src
OBJ_DIR := obj

SRC := $(SRC_DIR)/main_bonus.c \
	   $(SRC_DIR)/input_check_bonus.c \
	   $(SRC_DIR)/init_utils_bonus.c \
	   $(SRC_DIR)/dinner_bonus.c \
	   $(SRC_DIR)/dinner_utils_bonus.c \
	   $(SRC_DIR)/utils_bonus.c \
	   $(SRC_DIR)/time_utils_bonus.c \
	   $(SRC_DIR)/free_utils_bonus.c 

OBJ := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC:.c=.o))
INCLUDE := inc

CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread -I$(INCLUDE) #-fsanitize=thread

RM := rm -rf

$(NAME): $(OBJ)
		@$(CC) $(CFLAGS) $^ -o $(NAME)
		@echo "${GREEN} Created $(NAME)${RESET}"

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
