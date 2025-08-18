/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/08/18 17:59:07 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

// void	ft_clean(t_input *words, char *input)
// {
// 	if (input)
// 		free(input);
// 	// clean stack func needed
// 	if (words->word)
// 		free(words->word);
// 	if (words)
// 		free(words);
// }

// int	main(void)
// {
// 	t_input	*words;
// 	char	*input;
// 	int i;

// 	i = 0;
// 	words = NULL;
// 	while (42)
// 	{
// 		input = readline("Minishell % ");
// 		if (input == NULL)
// 			break ;
// 		if (*input == '\0' || !validate_input(input))
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		words = tokenize(words, input);
// 		while(words != NULL)
// 		{
// 			i += 1;
// 			printf("\n#%d. word: %s, type %d", i, words->word, words->type);
// 			words = words->next;
// 		}
// 		break ;

// 	}
// 	return (0);
// }

// copy envp to stack and after that mutate the PATH when execv usiung it
// int	main(int argc, char **argv, char **envp)

int	main(int argc, char **argv, char **envp)
{
	t_input	*command;
	char	*input;
	t_env	*my_env;
	char	*inputs[] = {"ls", "-l", NULL};
	char	*cmd[] = {"echo", "hello", NULL};
	int		i;

	my_env = init_env(envp);
	if (command == NULL)
		exit(3);
	command = initialize_command();
	i = 0;
	// while (command->argv[i])
	// {
	// 	printf("%s", command->argv[i]);
	// 	i++;
	// }
	what_command(command, my_env);
	// MAIN INPUT LOOP
	// while (42)
	// {
	// 	input = readline("Minishell % ");
	// 	if (input == NULL)
	// 		break ;
	// 	if (*input == '\0')
	// 	{
	// 		free(input);
	// 		continue ;
	// 	}
	// 	//what_command(input, my_env);
	// }
	return (0);
}

// function to copy envp to stack
// execve("/bin/echo", cmd, envp);
// words = malloc(sizeof(*words));
// if (words == NULL)
// 	exit(3);
// print_my_env(my_env); // function to print env list