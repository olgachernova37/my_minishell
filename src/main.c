/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/23 19:08:21 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_exit_status = 0;

void	free_input(t_input *words)
{
	t_input	*tmp;

	while (words)
	{
		tmp = words;
		words = words->next;
		free(tmp->word);
		free(tmp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_input	*words;
	char	*tmp;
	char	*input;
	char	**env_array;
	t_cmnd	*list;

	env = env_init(envp);
	read_history(".minishell_history");
	env_array = do_env_array(env, count_env_ls(env));
	init_signals();
	while (42)
	{
		words = NULL;
		input = readline("Minishell % ");
		signal(SIGINT, handler_sig_int);
		if (input == NULL)
		{
			char *exit_argv[2];
			exit_argv[0] = "exit";
			exit_argv[1] = NULL;
			exit_command_implementation(exit_argv, &env, env_array);
			break;
		}
		if (*input)
			add_history(input);
		if (*input == '\0' || !validate_input(input))
		{
			free(input);
			continue ;
		}
		input = dollar_extend(input, &env, g_exit_status);
		//print_extened_input(input);// "debug"
		words = tokenize(words, input);
		// creates linked list of tokenized input
		list = crt_cmnd_ls(words); // creats linked list of commands
		// print_cmnd_ls(list); // "debug" prints all stuff
		what_command(&list, &env, env_array);
	}
	write_history(".minishell_history");
	return (0);
}
