# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/25 12:58:33 by tiade-al          #+#    #+#              #
#    Updated: 2025/07/21 15:11:54 by tiade-al         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = philo

# Colors for terminal output
RESET = \033[0m
GREEN = \033[32m
YELLOW = \033[33m
RED = \033[31m
CYAN = \033[36m

# Source files
SRCS = srcs/activities.c\
	srcs/cleaners.c\
	srcs/clock.c\
	srcs/feast.c\
	srcs/helpers.c\
	srcs/init.c\
	srcs/main.c\
	srcs/parser.c\
	srcs/simulations.c\
	srcs/sync.c\

# Object files
OBJ = $(SRCS:srcs/%.c=objs/%.o)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror #-pthread -g .... -fsanitize=address

# Default target
all: $(NAME)

# Link executable
$(NAME): $(OBJ)
	@echo "$(YELLOW)[ LINKING ]$(RESET) Linking $(NAME)..."
	@$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@echo "$(GREEN)[ OK ]$(RESET) $(NAME) linked."
	@echo "$(GREEN)[ SUCCESS ]$(RESET) $(NAME) built successfully!"

# Compile source files
objs/%.o: srcs/%.c
	@mkdir -p objs
	@echo "$(CYAN)[ COMPILING ]$(RESET) $< -> $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@echo "$(RED)[ CLEAN ]$(RESET) Removing object files..."
	@rm -rf objs
	@echo "$(GREEN)[ OK ]$(RESET) Object files removed."

# Clean everything
fclean: clean
	@echo "$(RED)[ FCLEAN ]$(RESET) Removing $(NAME)..."
	@rm -f $(NAME)
	@echo "$(GREEN)[ OK ]$(RESET) All generated files removed."

# Rebuild
re: fclean all

# Phony targets
.PHONY: all clean fclean re
