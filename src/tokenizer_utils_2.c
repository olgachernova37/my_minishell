/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:39:29 by dt                #+#    #+#             */
/*   Updated: 2025/08/16 21:41:37 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// int	calc_len(t_input *new_word)
// {
// 	int	len;

// 	len = 0;
// 	while (new_word->word[len] != '\0')
// 		len++;
// 	return (len);
// }

// int	*tk_command(char *input, int res[3])
// {
// 	int	inword;
// 	int	i;

// 	i = 0;
// 	inword = 0;
// 	while (*input != '\0' && *input != 32 && *input != 9)
// 	{
// 		if (!inword)
// 		{
// 			inword = 1;
// 			res[0] = i;
// 		}
// 		i++;
// 		input++;
// 	}
// 	res[1] = i;
// 	res[2] = 0;
// 	return (res);
// }

// int	*tk_quotes(char *input, int res[3])
// {
// 	int	i;
// 	int	type;
// 	int	inword;

// 	i = 0;
// 	inword = 0;
// 	while (*input != '\0')
// 	{
// 		if (*input == 39 && !inword) // == '
// 		{
// 			type = 2;
// 			inword = 1;
// 			res[2] = 2;
// 			res[0] = i;
// 		}
// 		else if (*input == 34 && !inword) // == "
// 		{
// 			type = 3;
// 			inword = 1;
// 			res[0] = i;
// 			res[2] = 3;
// 		}
// 		else if (*input == 39 && inword && type == 2)
// 		{
// 			res[1] = i;
// 			break ;
// 		}
// 		else if  (*input == 34 &&inword && type == 3)
// 		{
// 			res[1] = i;
// 			break ;
// 		}
// 		input++;
// 		i++;
// 	}
// 	return (res);
// }