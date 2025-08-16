/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:48 by dt                #+#    #+#             */
/*   Updated: 2025/08/16 21:41:16 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	check_backslash(char *input)
// {
// 	while (*input != '\0')
// 	{
// 		if (*input == 92)
// 			return (1);
// 		else
// 			input++;
// 	}
// 	return (0);
// }

// int	has_simocolon(char *input)
// {
//     while (*input != '\0')
// 	{
// 		if (*input == 59)
// 			return (1);
// 		else
// 			input++;
// 	}
// 	return (0);
// }

// bool validate_input(char *input)
// {
// 	if (!input)
// 		return false;
// 	if (check_unclosed_quotes(input))
// 	{
// 		printf("minishell: syntax error: unclosed quotes\n");
// 		return false;
// 	}
// 	if (check_backslash(input))
// 	{
// 		printf("minishell: syntax error: unexpected '\\'\n");
// 		return false;
// 	}
// 	if (has_simocolon(input))
// 	{
// 		printf("minishell: syntax error: unexpected ';'\n");
// 		return false;
// 	}
// 	return true;
// }
