# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 15:18:15 by olcherno          #+#    #+#              #
#    Updated: 2025/10/23 16:40:36 by olcherno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc # cc
# CFLAGS = -g -Wall -Wextra -Werror
NAME = minishell
SRCDIR = src
OBJDIR = obj
LIBFTDIR = libs/libft
FTPRINTF_DIR = libs/libftprintf
COMMAND_DIR = src/commands

SRC_OP = cmnd_ls_utils_0.c cmnd_ls_utils_1.c \
crt_cmnd_ls.c do_env_array.c main.c env_init.c \
tokenizer.c tokenizer_utils.c tokenizer_utils_2.c\
utils.c validate_input.c validate_input_2.c what_command.c dollar_ls_utils.c \
dollar_ls_0.c dollar_ls_1.c signal.c main_utils.c\

SRC_DATA = buildin_commands/cd_command_implementation.c    buildin_commands/exit_command_implementation.c    buildin_commands/pwd_command_implementation.c \
buildin_commands/echo_command_implementation.c  buildin_commands/export_command_implementation.c  buildin_commands/unset_command_implementation.c \
buildin_commands/other_commands.c \
buildin_commands/other_commands2.c buildin_commands/cd_command_implementation2.c buildin_commands/export_command_implementation2.c  \
buildin_commands/export_command_implementation3.c buildin_commands/export_command_implementation4.c buildin_commands/export_command_implementation5.c


SRC = $(SRC_OP) $(SRC_DATA)

OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
SRCS = $(addprefix $(SRCDIR)/, $(SRC))

# Rules of files
$(NAME): $(OBJS) $(LIBFTDIR)/libft.a $(FTPRINTF_DIR)/libftprintf.a
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFTDIR) -lft -L$(FTPRINTF_DIR) -lftprintf -lreadline  -o $(NAME) 
# add -ltinfo
# Create necessary directories for object files
$(OBJDIR):
	@mkdir -p $(OBJDIR)/main

# Compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
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
