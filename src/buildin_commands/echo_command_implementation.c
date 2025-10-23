/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command_implementation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:26:59 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/23 16:44:17 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_command_implementation(t_cmnd **cmnd_ls, t_env **env)
{
	int	i;
	int	y;
	int	n_flag;

	n_flag = 0;
	i = 1;
	y = 1;
	if ((*cmnd_ls)->argv[i] && ft_strncmp((*cmnd_ls)->argv[1], "-n", 3) == 0)
	{
		n_flag = 1;
		y = 2;
	}
	while ((*cmnd_ls)->argv[y] != NULL)
	{
		printf("%s", (*cmnd_ls)->argv[y]);
		if ((*cmnd_ls)->argv[y + 1])
			printf(" ");
		y++;
	}
	if (n_flag == 0)
		printf("\n");
	return (0);
}
