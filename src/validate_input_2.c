/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:44:09 by dt                #+#    #+#             */
/*   Updated: 2025/08/16 21:41:20 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	find_sq(char *input, int *signl_q)
// {
// 	int	i;

// 	i = 1;
// 	input++;
// 	while (*input != 39 && *input != '\0')
// 	{
// 		input++;
// 		i++;
// 	}
// 	if (*input != 39)
// 		*signl_q = 0;
// 	return (i+1);
// }

// int	find_dq(char *input, int *double_q)
// {
// 	int	i;

// 	i = 1;
// 	input++;
// 	while (*input != 34 && *input != '\0')
// 	{
// 		input++;
// 		i++;
// 	}
// 	if (*input != 34)
// 		*double_q = 0;
// 	return (i+1);
// }

// int	check_unclosed_quotes(char *input)
// {
// 	int	singl_q;
// 	int	double_q;

// 	singl_q = 1;
// 	double_q = 1;
// 	while (*input != '\0')
// 	{
// 		if (*input == 39)
// 			input += find_sq(input, &singl_q);
// 		else if (*input == 34)
// 			input += find_dq(input, &double_q);
// 		else
// 			input++;
// 	}
// 	if (singl_q && double_q)
// 		return (0);
// 	return (1);
// }
