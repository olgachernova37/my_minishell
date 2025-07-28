/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/07/28 20:22:24 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

void	ft_clean(t_input *words, char *input)
{
	if (input)
		free(input);
	// clean stack func needed
	if (words->word)
		free(words->word);
	if (words)
		free(words);
}

// copy envp to stack and after that mutate the PATH when execv usiung it
// int	main(int argc, char **argv, char **envp)
int	main(int argc, char **argv, char **envp)
{
	char *cmd[] = {"echo", "hello", NULL};
	t_input	*words;
	char	*input;
	t_env	*my_env;

	my_env = init_env(envp);
	
	// function to copy envp to stack
	char *inputs[] = {"ls", "-l", NULL};
	execve("/bin/echo", cmd, envp);
	

	words = malloc(sizeof(*words));
	if (words == NULL)
		exit(3);
	print_my_env(my_env); // function to print env list
	while (42)
	{
		input = readline("Minishell % ");
		if (input == NULL)
			break ;
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		// olga(input, words);
	}
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
//    (void)argc;
//     (void)argv;
//     (void)envp;
//     ft_printf("Welcome to Minishell!\n");
//     return (0);
// }