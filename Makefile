# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 14:40:15 by aelkheta          #+#    #+#              #
#    Updated: 2024/07/03 20:22:45 by aelkheta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
RLFLAG = -lreadline
SRCDIR = ./srcs
OBJDIR = ./objs

EXECDIR = ./exec

SRC = 	$(SRCDIR)/minishell.c \
		$(SRCDIR)/built_in_cmd1.c \
		$(SRCDIR)/built_in_cmd2.c \
		$(SRCDIR)/cleanup.c \
		$(SRCDIR)/mini_utiles.c \
		$(SRCDIR)/tokenizer.c \
		$(SRCDIR)/parsing.c \
		$(SRCDIR)/parsing_utiles.c \
		$(EXECDIR)/allcmd.c\
		$(EXECDIR)/error.c\
		$(EXECDIR)/excute.c\
		$(EXECDIR)/here_doc.c\
		$(EXECDIR)/link_list.c\
		$(EXECDIR)/main.c\
		$(EXECDIR)/one_cmd.c\
		$(EXECDIR)/open_file.c\

OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC)) # for pathern substitution // $(patsubst pattern,replacement,text)

LIBFT = ./libraries/libft/libft.a

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "Building..."
	@$(CC) $(CFLAGS) $(OBJ) $(RLFLAG) $(LIBFT) -o $@
	@echo "Building done"

clean:
	@echo "Removing object files..."
	@rm -rf $(OBJDIR)/*.o
	@echo "Removing object files done"

fclean: clean
	@echo "Removing program name..."
	@rm -f $(NAME)
	@echo "Removing program name done"

re: fclean all

.PHONY: all clean fclean re
