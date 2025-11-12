# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danfern3 <danfern3@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/10 09:34:42 by danfern3          #+#    #+#              #
#    Updated: 2025/11/03 13:17:15 by danfern3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# * Program name
NAME = philo

# * Compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
CFLAGS += -fsanitize=address

# * Removal
RM = rm -f

# * Includes
INCLUDES = -I ./inc/

# * Objects dir
OBJ_DIR = ./src/obj/

# * Sources files
PHILO_DIR = ./src/
PHILO_SRCS = $(shell ls $(PHILO_DIR) | grep -E ".+\.c")
SRCS = $(PHILO_SRCS)

# * Creating object files
OBJS = $(addprefix $(OBJ_DIR), $(PHILO_SRCS:.c=.o))

# ! RULES
# ? Links a .c (and .h if needed) to its .o file
$(OBJ_DIR)%.o: $(PHILO_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ? main program compilation
$(NAME): $(OBJS)
	@clear
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "Compiling $(NAME)"

# ? Compiles the whole program/library
all: obj $(NAME)

# ? Creates the folder for .o files
obj:
	@mkdir -p $(OBJ_DIR)

# ? Removes the object files
clean:
	@$(RM) $(OBJS)
	@echo "Removing .o files"

# ? Removes both object and executable files
fclean: clean
	@$(RM) $(NAME)
	@echo "Removing $(NAME)"

# ? Rebuilds the program/library
re: fclean all
	@echo "Rebuilding $(NAME)"

# ! Automating / Debugging rules

INPUT = 2 2 2 2 2

run: all
	clear
	./$(NAME) $(INPUT)

valgrind: all
	clear
	valgrind ./$(NAME) $(INPUT)

debug: all
	clear
	gdb ./$(NAME)

# Protects all rules from files with same name
.PHONY: all obj clean fclean re run valgrind debug

# Indicates the main rule to be executed when only 'make' is called
.GOAL: all