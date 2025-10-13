/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/09/09 21:31:06 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		exit_status = 0;

// func for tests
void	print_og_env(char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return ;
	while (envp[i])
		printf("%s\n", envp[i++]);
}

// test main
int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**array;
	t_input	*words;
	t_env	*env;
	t_env	*env_tmp;
	t_input	*tmp_wrds;
	char	**env_array;
	int		i;

	env = env_init(envp);
	init_signals();
	read_history(".minishell_history");
	while (42)
	{
		i = 0;
		tmp_wrds = NULL;
		array = NULL;
		words = NULL;
		input = readline("Minishell % ");
		signal(SIGINT, "signal_handler");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		if (*input == '\0' || !validate_input(input))
		{
			free(input);
			continue ;
		}
		words = tokenize(words, input);
		tmp_wrds = words;
		while (tmp_wrds != NULL)
		{
			i += 1;
			// printf("\n#%d. word: %s, type %d", i, tmp_wrds->word,
			tmp_wrds->type;
			tmp_wrds = tmp_wrds->next;
		}
		// printf("\n\n");
		array = do_input_array(words, count_list_input(words));
		///
		// i = 0;
		// array = do_input_array(words, count_list_input(words));
		// printf("\n\nLenght of the list: %d\n\n", count_list_input(words));
		// while (array[i])
		// 	printf("%s -> ", array[i++]);
		// printf("%s\n", array[i]);
		///
		env_array = do_env_array(env, count_list_env(env));
		what_command(array, &env, env_array);
		free(input);
		free(words);
	}
	write_history(".minishell_history");
	return (0);
}

// demo main
// int	main(int argc, char **argv, char **envp)
// {
// 	t_input	*words;
// 	t_env	*env;
// 	char	*input;
// 	char	**array;
// 	char 	**env_array;

// 	env = env_init(envp);
// 	env_array = do_env_array(env, count_list_env(env));
// 	while (42)
// 	{
// 		array = NULL;
// 		words = NULL;
// 		input = readline("Minishell % ");
// 		if (input == NULL)
// 			break ;
// 		if (*input == '\0' || !validate_input(input))
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		words = tokenize(words, input);
// array = do_array(words, count_list_input(words));

// 		free(input);
// 		free(words);
// 	}
// 	return (0);
// }
