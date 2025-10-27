/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:48 by dt                #+#    #+#             */
/*   Updated: 2025/10/27 21:33:33 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_backslash(char *input)
{
	int	in_q;

	in_q = 0;
	while (*input != '\0')
	{
		if (*input == 34 && !in_q)
			in_q = 1;
		else if (*input == 39 && !in_q)
			in_q = 2;
		else if (*input == 34 && in_q == 1)
			in_q = 0;
		else if (*input == 39 && in_q == 2)
			in_q = 0;
		if (*input == 92 && !in_q)
			return (1);
		input++;
	}
	return (0);
}

int	has_simocolon(char *input)
{
	int	in_q;

	in_q = 0;
	while (*input != '\0')
	{
		if (*input == 34 && !in_q)
			in_q = 1;
		else if (*input == 39 && !in_q)
			in_q = 2;
		else if (*input == 34 && in_q == 1)
			in_q = 0;
		else if (*input == 39 && in_q == 2)
			in_q = 0;
		if (*input == 59 && !in_q)
			return (1);
		input++;
	}
	return (0);
}

int	has_double_and_or_pipe(char *input)
{
	int	in_q;

	in_q = 0;
	while (*input != '\0')
	{
		if (*input == 34 && !in_q)
			in_q = 1;
		else if (*input == 39 && !in_q)
			in_q = 2;
		else if (*input == 34 && in_q == 1)
			in_q = 0;
		else if (*input == 39 && in_q == 2)
			in_q = 0;
		if (!in_q && (((*input == 38 && *(input + 1) == 38)) || (*input == 124)
				&& *(input + 1) == 124))
			return (1);
		input++;
	}
	return (0);
}

bool	validate_input(char *input)
{
	if (!input)
		return (false);
	if (has_unclosed_quotes(input))
		return (drop_false("Minishell:  syntax error: unclosed quotes\n"));
	if (has_backslash(input))
		return (drop_false("Minishell: syntax error: unexpected '\\'\n"));
	if (has_simocolon(input))
		return (drop_false("Minishell: syntax error: unexpected ';'\n"));
	if (has_double_and_or_pipe(input))
		return (drop_false("Minishell: syntax error: unexpected '&&'or'||'\n"));
	return (true);
}

//not for vaidation
void	security_fd(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}
