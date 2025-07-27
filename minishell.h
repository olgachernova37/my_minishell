/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:31:21 by olcherno          #+#    #+#             */
/*   Updated: 2025/07/27 20:29:33 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <term.h>
# include <curses.h>
# include <termios.h>
# include <stdint.h>
# include <sys/ioctl.h>

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libs/libft/libft.h"
# include "libs/libftprintf/ft_printf.h"



typedef enum{
    TOKEN_WORD, //0
    TOKEN_PIPE, //1
    TOKEN_REDIR_IN, //2
    TOKEN_REDIR_OUT, //3
} token_type_t;

typedef struct s_input
{
    //after parse_input type = "TOKEN_WORD/TOKEN_PIPE/TOKEN_REDIR_IN etc..."
    token_type_t    type;
	struct s_input	*next;
	char			*word;
} t_input;

typedef struct s_env
{
    char			*key;
    char			*value;
    struct s_env	*next;
} t_env;

//parsing.c
void	tokenize(t_input *words, char *input);
t_input	*make_word(t_input *words, char *input);

//utils.c
size_t	ft_strlen(const char *s);

//env
t_env *init_env(char **envp);
void print_my_env(t_env *env);


#endif