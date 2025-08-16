/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:31:21 by olcherno          #+#    #+#             */
/*   Updated: 2025/08/16 23:02:12 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs/libft/libft.h"
# include "libs/libftprintf/ft_printf.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

typedef enum{
    TOKEN_WORD, //0
    TOKEN_PIPE, //1
    TOKEN_REDIR_IN, //2
    TOKEN_REDIR_OUT, //3
} token_type_t;

typedef struct s_input
{
	// after parse_input type = "TOKEN_WORD/TOKEN_PIPE/TOKEN_REDIR_IN etc..."
	token_type_t	type;
	struct s_input	*next;
	char			*word;
}					t_input;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

// parsing.c
t_input				*make_word(t_input *words, char *input);

// utils.c
size_t				ft_strlen(const char *s);

// env
t_env				*init_env(char **envp);
void				print_my_env(t_env *env);

// validate_input.c
int					find_sq(char *input, int *signl_q);
int					find_dq(char *input, int *double_q);
int					check_unclosed_quotes(char *input);

// validate_input_2.c
int					check_backslash(char *input);
int					has_simocolon(char *input);
bool				validate_input(char *input);

// tokenizer.c
int					add_node(t_input **words, t_input *new_word, int tk_len);
t_input				*do_node(int start_end[], char *input);
int					creat_tokenz(char *input, t_input **words, int tk_len);
t_input				*tokenize(t_input *words, char *input);

// tokenizer_utils_2.c
int					calc_len(t_input *new_word);
int					*tk_command(char *input, int res[3]);
int					*tk_quotes(char *input, int res[3]);

// tokenizer_utils.c
int					*tk_flag(char *input, int res[3]);
int					*tk_in_here(char *input, int res[3]);
int					*tk_out_appnd(char *input, int res[3]);
int					*tk_pipe(char *input, int res[3]);
int					*tk_envp_v(char *input, int res[3]);

// utils.c
size_t				ft_strlen(const char *s);

// what_command.c
bool				is_command_buildin(char *input);
void				what_command(char *input, t_env *my_env);
void 				echo_command_implementation(char *input);
void 				pwd_command_implementation(void);
void 				export_command_implementation(t_env *my_env);
void 				unset_command_implementation(t_env *my_env);
void 				cd_command_implementation(t_env *my_env);
void 				exit_command_implementation(t_env *my_env);	


#endif