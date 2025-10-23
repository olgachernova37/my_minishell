/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by dt                #+#    #+#             */
/*   Updated: 2025/10/23 01:07:10 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_delimiter(char c)
{
	return (!(c >= 48 && c <= 57 || c >= 65 && c <= 90 || c >= 97 && c <= 122
			|| c == 95));
}

int	another_one(int i, char *input, t_quote_state *st)
{
	return (input[i] == '$' && st->type == 0 && (input[i + 1] == '\'' || input[i
			+ 1] == '"'));
}

int	if_logic(int i, char *input, t_quote_state *st)
{
	return (input[i] == '$' && input[i + 1] && ((input[i + 1] == '?'
				|| (is_delimiter(input[i + 1]) == 0) && (st->type == '"'
					|| st->type == 0))));
}

// clean stack func needed
void	ft_clean(t_input *words, char *input)
{
	if (input)
		free(input);
	if (words->word)
		free(words->word);
	if (words)
		free(words);
}

size_t	ft_strlenn(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		exit(1);
	while (*s != '\0' && *s != 32)
	{
		i++;
		s++;
	}
	return (i);
}
