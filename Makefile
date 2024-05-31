# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 14:40:15 by aelkheta          #+#    #+#              #
#    Updated: 2024/05/31 09:43:27 by aelkheta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
RLFLAG = -lreadline
SRCDIR = ./srcs
OBJDIR = ./objs

SRC = 	$(SRCDIR)/minishell.c \
		$(SRCDIR)/built_in_cmd1.c \
		$(SRCDIR)/built_in_cmd2.c \
		$(SRCDIR)/cleanup.c \
		$(SRCDIR)/mini_utiles.c \
		$(SRCDIR)/tokenizer.c \

OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC)) # for pathern substitution // $(patsubst pattern,replacement,text)

LIBFT = ./libraries/libft/libft.a

all: $(NAME)
	@./compiler/compiling

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(RLFLAG) $(LIBFT) -o $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@./compiler/cleaning
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
