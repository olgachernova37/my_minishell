/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:30:55 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/27 21:34:07 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_command_arrays(t_cmnd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv && cmd->argv[i])
		free(cmd->argv[i++]);
	free(cmd->argv);
	i = 0;
	while (cmd->full_argv && cmd->full_argv[i])
		free(cmd->full_argv[i++]);
	free(cmd->full_argv);
	i = 0;
	while (cmd->argv_type && cmd->argv_type[i])
		free(cmd->argv_type[i++]);
	free(cmd->argv_type);
}

void	free_redirections(t_rdrs *rdrs)
{
	t_rdrs	*rdr_tmp;

	while (rdrs)
	{
		rdr_tmp = rdrs;
		rdrs = rdrs->next;
		free(rdr_tmp->filename);
		free(rdr_tmp);
	}
}

void	free_list(t_cmnd *list)
{
	t_cmnd	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_command_arrays(tmp);
		free_redirections(tmp->rdrs);
		free(tmp);
	}
}
