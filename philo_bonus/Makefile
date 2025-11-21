# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danfern3 <danfern3@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/10 09:34:42 by danfern3          #+#    #+#              #
#    Updated: 2025/11/18 10:26:18 by danfern3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# * Program name
NAME = philo_bonus

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
PHILO_BONUS_DIR = ./src/
PHILO_BONUS_SRCS = $(shell ls $(PHILO_BONUS_DIR) | grep -E ".+\.c")
# PHILO_BONUS_SRCS =	dinner_bonus.c \
# 				encapsulation_bonus.c \
# 				init_bonus.c \
# 				main_bonus.c \
# 				monitor_bonus.c \
# 				parser_bonus.c \
# 				safe_functions_bonus.c \
# 				status_bonus.c \
# 				synchro_utils_bonus.c \
# 				utils_bonus.c
SRCS = $(PHILO_BONUS_SRCS)

# * Creating object files
OBJS = $(addprefix $(OBJ_DIR), $(PHILO_BONUS_SRCS:.c=.o))

# ! RULES
# ? Links a .c (and .h if needed) to its .o file
$(OBJ_DIR)%.o: $(PHILO_BONUS_DIR)%.c
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

# INPUT = 1 310 200 100

# run: all
# 	clear
# 	./$(NAME) $(INPUT)

# valgrind: all
# 	clear
# 	valgrind ./$(NAME) $(INPUT)

# debug: all
# 	clear
# 	gdb ./$(NAME)

# Protects all rules from files with same name
.PHONY: all obj clean fclean re run valgrind debug

# Indicates the main rule to be executed when only 'make' is called
.GOAL: all