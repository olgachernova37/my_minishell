/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:41:29 by dt                #+#    #+#             */
/*   Updated: 2025/08/16 21:41:32 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// //add check for the empty - (No such file or directory)
// int	*tk_flag(char *input, int res[3])
// {
// 	int	inword;
// 	int	i;

// 	i = 0;
// 	inword = 0;
// 	while (*input != '\0' && *input != 32 && *input != 9)
// 	{
// 		if (!inword && *input == 45) // == '-'
// 		{
// 			inword = 1;
// 			res[0] = i; // flag without '-'
// 			i++;
// 		}
// 		else if (inword && *input == 45) ///.........
// 			break;
// 		else 
// 			i++;
// 		input++;
// 	}
// 	res[1] = i;
// 	res[2] = 1;
// 	return (res);
// }

// int	*tk_out_appnd(char *input, int res[3])
// {
// 	int	i;

// 	i = 0;
// 	while (*input != '\0')
// 	{
// 		if (*input == '>') // >
// 		{
// 			res[0] = i;
// 			res[1] = ++i;
// 			res[2] = 6;
// 			if (*(input + 1) == '>') // >>
// 			{
// 				res[1] = ++i;
// 				res[2] = 7;
// 				break ;
// 			}
// 		}
// 		input++;
// 		i++;
// 	}
// 	return (res);
// }

// int	*tk_in_here(char *input, int res[3])
// {
// 	int	i;

// 	i = 0;
// 	while (*input != '\0')
// 	{
// 		if (*input == '<') // <
// 		{
// 			res[0] = i;
// 			res[1] = ++i;
// 			res[2] = 5;
// 			if (*(input + 1) == '<') // <<
// 			{
// 				res[1] = ++i;
// 				res[2] = 8;
// 				break;
// 			}
// 		}
// 		input++;
// 		i++;
// 	}
// 	return (res);
// }

// int	*tk_pipe(char *input, int res[3])
// {
// 	int	i;

// 	i = 0;
// 	while (*input != '\0')
// 	{
// 		if (*input == '|')
// 		{
// 			res[0] = i;
// 			res[1] = i + 1;
// 			break ;
// 		}
// 		else
// 			input++;
// 		i++;
// 	}
// 	res[2] = 4;
// 	return (res);
// }

// int	*tk_envp_v(char *input, int res[3])
// {
// 	int	i;
// 	int	inword;

// 	i = 0;
// 	inword = 0;
// 	while (*input != '\0')
// 	{
// 		if (*input == '$' && !inword)
// 		{
// 			res[0] = i;
// 			inword = 1;
// 		}
// 		else if (inword && *input != 32 && *input != 9)
// 		{
// 			input++;
// 			i++;
// 		}
// 		else if (inword)
// 			break ;
// 	}
// 	res[1] = i;
// 	res[2] = 9;
// 	return (res);
// }
