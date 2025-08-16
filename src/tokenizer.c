/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by dt                #+#    #+#             */
/*   Updated: 2025/08/16 21:41:28 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// // returns new node, parametrs: s-e-type,
// t_input	*do_node(int start_end[], char *input)
// {
// 	int		len;
// 	char	*res;
// 	int		i;
// 	t_input	*new_node;
	
// 	i = 0;
// 	new_node = malloc(sizeof(t_input));
// 	if (new_node == NULL)
// 		return (NULL);
// 	len = start_end[1] - start_end[0];
// 	res = malloc(sizeof(char) * (len + 1));
// 	if (res == NULL)
// 	{
// 		// probably should be added free(words) if (words != NULL)
// 		free(new_node);
// 		return (NULL);
// 	}
// 	while (i < len)
// 	{
// 		res[i] = *(input + i);
// 		i++;
// 	}
// 	res[i] = '\0';
// 	new_node->word = res;
// 	new_node->next = NULL;
// 	new_node->type = start_end[2];
// 	return (new_node);
// }

// int	add_node(t_input **words, t_input *new_word, int tk_len)
// {
// 	t_input	*tmp;

// 	if (*words == NULL)
// 	{
// 		*words = new_word;
// 		tk_len = calc_len(new_word);
// 		return (tk_len);
// 	}
// 	tmp = *words;
// 	while (tmp->next != NULL)
// 		tmp = tmp->next;
// 	tmp->next = new_word;
// 	if (new_word->type == 0) // if first word
// 		tk_len = calc_len(new_word);
// 	else if (new_word->type == 1 || new_word->type == 9)
// 		tk_len = calc_len(new_word); //+1 for skiped - / $
// 	else if (new_word->type == 2 || new_word->type == 3)
// 		tk_len = calc_len(new_word) + 2; //+2 for skiped '' / ""
// 	else if (new_word->type == 4 || new_word->type == 5 || new_word->type == 6
// 		|| new_word->type == 7 || new_word->type == 8)
// 		tk_len = calc_len(new_word); // if | > >> << <
// 	return (tk_len);
// }

// int	creat_tokenz(char *input, t_input **words, int tk_len)
// {
// 	int	type;
// 	int	res[3];
// 	int	len;

// 	// command == . / A-Z a-z
// 	if ((*input >= 65 && *input <= 90) || (*input >= 97 && *input <= 122)
// 		|| *input == 95 || *input == 46 || *input == 97)
// 		return (add_node(words, do_node(tk_command(input, res), input), tk_len));
// 	else if (*input == '-') // flag
// 		return (add_node(words, do_node(tk_flag(input, res), input), tk_len));	
// 	else if (*input == 39 || *input == 34) // quots
// 		return (add_node(words, do_node(tk_quotes(input, res), input), tk_len));	
// 	else if (*input == 124) // |
// 	return (add_node(words, do_node(tk_pipe(input, res), input), tk_len));	
// 	else if (*input == 36) // $ (environmental var)
// 		return (add_node(words, do_node(tk_envp_v(input, res), input), tk_len));	
// 	else if (*input == 62) // >> >
// 		return (add_node(words, do_node(tk_out_appnd(input, res), input), tk_len));	
// 	else if (*input == 60) // << <
// 		return (add_node(words, do_node(tk_in_here(input, res), input), tk_len));
// 	// else condition is needed
// 	return (0); // <<=--
// }

// t_input	*tokenize(t_input *words, char *input)
// {
// 	int	tk_len;

// 	tk_len = 0;
// 	// printf("tk_len: %d", tk_len);
// 	// printf("\nInput: %d", tk_len);
// 	while (*input != '\0')
// 	{
// 		if (*input != 32 && *input != 9)
// 		{
// 			tk_len = creat_tokenz(input, &words, tk_len);
// 			// printf("\n.tk_len: %d", tk_len);
// 			input += tk_len;
// 		}
// 		else // if *input = 32 || *input = 9
// 		{
// 			input++;
// 		}
// 	}
// 	return (words);
// }
