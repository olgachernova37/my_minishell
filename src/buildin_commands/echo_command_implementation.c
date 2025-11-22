/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command_implementation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:26:59 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/06 13:09:51 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo_command_implementation(t_cmnd **cmnd_ls)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = 1;
	while ((*cmnd_ls)->argv[i] && is_n_flag((*cmnd_ls)->argv[i]))
	{
		n_flag = 1;
		i++;
	}
	while ((*cmnd_ls)->argv[i] != NULL)
	{
		write(STDOUT_FILENO, (*cmnd_ls)->argv[i],
			ft_strlen((*cmnd_ls)->argv[i]));
		if ((*cmnd_ls)->argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (n_flag == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
