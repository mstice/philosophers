NAME := philo

SRC_DIR := src
OBJ_DIR := obj

SRC := $(SRC_DIR)/main.c \
	   $(SRC_DIR)/input_check.c \
	   $(SRC_DIR)/utils.c

OBJ := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC:.c=.o))
INCLUDE := inc

CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread -g3 -I$(INCLUDE)

RM := rm -rf

$(NAME): $(OBJ)
		@$(CC) $(CFLAGS) $^ -o $(NAME)

$(OBJ): $(OBJ_DIR)%.o:$(SRC_DIR)%.c
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(CFLAGS) -c -o $@ $^

all: $(NAME)

clean:
		@$(RM) $(OBJ) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
