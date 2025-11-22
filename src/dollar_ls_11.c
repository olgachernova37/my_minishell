/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_ls_11.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:54:13 by dtereshc          #+#    #+#             */
/*   Updated: 2025/11/20 20:33:32 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_xtnd	*handle_empty_node(char *input, t_xtnd *xtnd_node,
		t_quote_state *st)
{
	if (is_literal_dollar(input))
	{
		xtnd_node->new = ft_strdup("$");
		if (!xtnd_node->new)
			exit(2);
		xtnd_node->og_len = 1;
		xtnd_node->len_dif = 0;
	}
	else if (*input == '?')
	{
		free_xtnds(&xtnd_node);
		xtnd_node = crt_xtnd_ex_status(st);
	}
	else
	{
		xtnd_node->new = ft_strdup("");
		if (!xtnd_node->new)
			exit(2);
		xtnd_node->og_len = calc_og(input);
		xtnd_node->len_dif = ft_strlen(xtnd_node->new) - xtnd_node->og_len;
	}
	return (xtnd_node);
}

t_xtnd	*crt_xtnd_logic(char *input, t_env **env, t_quote_state *st)
{
	t_xtnd	*xtnd_node;

	xtnd_node = xtnd_env(input, env);
	if (!xtnd_node)
		exit(41);
	if (!xtnd_node->new)
		xtnd_node = handle_empty_node(input, xtnd_node, st);
	return (xtnd_node);
}
