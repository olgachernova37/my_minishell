/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implem_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/20 20:33:32 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_heredoc(char *delimiter, int counter, t_cleanup *cleanup)
{
	char	*filename;
	int		fd;
	int		result;

	filename = get_heredoc_filename(counter);
	if (!filename)
		return (-1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror(filename);
		free(filename);
		return (-1);
	}
	result = write_heredoc_content(fd, delimiter, filename, cleanup);
	close(fd);
	free(filename);
	if (result != 0)
		return (-1);
	return (0);
}
