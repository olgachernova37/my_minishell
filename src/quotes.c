/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:48 by dt                #+#    #+#             */
/*   Updated: 2025/07/28 19:34:59 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// check if input is valid:
// all "" '' and check if

int	find_sq(char *input, int signl_q)
{
	while (*input != 39 && *input)
		input++;
	if (*input != 39)
		signl_q = 0;
	return (signl_q);
}

int	find_dq(char *input, int double_q)
{
	while (*input != 34 && *input)
		input++;
	if (*input != 34)
		double_q = 0;
	return (double_q);
}

int	has_unclosed_quotes(char *input)
{
	int	singl_q;
	int	double_q;

	singl_q = 1;
	double_q = 1;
	while (*input != '\0')
	{
		if (*input == 39)
			find_sq(input, singl_q);
		else if (*input == 34)
			find_dq(input, double_q);
		else
			input++;
	}
	if (singl_q && double_q)
		return (0);
	else
		return (1);
}

void	has_unclosed_quotes(char *input)
{
}

void	has_unclosed_quotes(char *input)
{
}

void	validate_input(char *input)
{
	if (has_unclosed_quotes(input))
	{
		printf("minishell: syntax error: unclosed quotes\n");
		return ;
	}
	if (has_backslash(input))
	{
		printf("minishell: syntax error: unexpected '\\'\n");
		return ;
	}
	if (has_semicolon(input))
	{
		printf("minishell: syntax error: unexpected ';'\n");
		return ;
	}
}