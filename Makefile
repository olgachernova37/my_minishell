# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 15:18:15 by olcherno          #+#    #+#              #
#    Updated: 2025/08/16 22:15:16 by olcherno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc # cc 
# CFLAGS = -g -Wall -Wextra -Werror
NAME = minishell
SRCDIR = src
OBJDIR = obj
LIBFTDIR = libs/libft
FTPRINTF_DIR = libs/libftprintf

SRC_OP = main.c env_init.c tokenizer.c tokenizer_utils.c  validate_input_2.c exit.c quotes.c  tokenizer_utils_2.c  utils.c validate_input.c what_command.c \
# 		buildin_commands/echo.c buildin_commands/env.c buildin_commands/export.c buildin_commands/pwd.c \
# 		buildin_commands/unset.c buildin_commands/cd.c buildin_commands/exit2.c buildin_commands/exit3.c \
# 		buildin_commands/exit4.c buildin_commands/exit5.c buildin_commands/exit6.c buildin_commands/exit7.c \
# 		buildin_commands/exit8.c buildin_commands/exit9.c buildin_commands/exit10.c
#SRC_DATA = 
SRC = $(SRC_OP) $(SRC_DATA)

OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
SRCS = $(addprefix $(SRCDIR)/, $(SRC))

# Rules of files
$(NAME): $(OBJS) $(LIBFTDIR)/libft.a $(FTPRINTF_DIR)/libftprintf.a
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFTDIR) -lft -L$(FTPRINTF_DIR) -lftprintf -lreadline -o $(NAME)

# Create necessary directories for object files
$(OBJDIR):
	mkdir -p $(OBJDIR)/main $(OBJDIR)/commands

# Compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(SRCDIR) -I$(LIBFTDIR) -I$(FTPRINTF_DIR) -c $< -o $@

# Rules to build the libraries # making makefile of libft
$(LIBFTDIR)/libft.a:
	$(MAKE) -C $(LIBFTDIR) 

$(FTPRINTF_DIR)/libftprintf.a:    # making makefile of printf
	$(MAKE) -C $(FTPRINTF_DIR)

# Rules of actions
.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(FTPRINTF_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	$(MAKE) -C $(FTPRINTF_DIR) fclean

re: fclean all