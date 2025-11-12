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
NAME = pipex

# * Compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# CFLAGS += -fsanitize=address

# * Removal
RM = rm -f

# * Includes
INCLUDES = -I ./inc/headers -I ./inc/libft/inc/headers/

# * Objects dir
OBJ_DIR = ./src/obj/

# * Sources files
PIPEX_DIR = ./src/
PIPEX_SRCS = $(shell ls $(PIPEX_DIR) | grep -E ".+\.c")
SRCS = $(PIPEX_SRCS)

# * Creating object files
OBJS = $(addprefix $(OBJ_DIR), $(PIPEX_SRCS:.c=.o))

# * LIBFT
LIBFT_DIR = ./inc/libft/
LIBFT = ./inc/libft/libft.a

# ! RULES
# ? Links a .c (and .h if needed) to its .o file
$(OBJ_DIR)%.o: $(PIPEX_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ? main program compilation
$(NAME): $(OBJS) $(LIBFT)
	@clear
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "Compiling $(NAME)"

# ? libft compilation
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all
	@echo "Compiling libft"

# ? Compiles the whole program/library
all: obj $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

# ? Removes the object files
clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "Removing .o files"

# ? Removes both object and executable files
fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "Removing $(NAME)"

# ? Rebuilds the program/library
re: fclean all
	@echo "Rebuilding $(LIBFT)"
	@$(MAKE) -C $(LIBFT_DIR) re
	@echo "Rebuilding $(NAME)"

# ! Automating / Debugging rules
# INPUT = infile "ls -l" "grep Oct" "wc -l" outfile
INPUT = infile "ls -l" "wc -l" outfile

run: all
	clear
	./$(NAME) $(INPUT)

run2: all
	clear
	./$(NAME) infile "ls" "grep Make" outfile

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