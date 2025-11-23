/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implem_heredoc1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/23 16:03:27 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_base_filename(char *pid_str)
{
	char	*temp;
	char	*base_filename;

	temp = ft_strjoin("/tmp/.heredoc_", pid_str);
	if (!temp)
		return (NULL);
	base_filename = ft_strjoin(temp, "_");
	free(temp);
	return (base_filename);
}

void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
	}
}

int	process_heredoc_line(int fd, char *delimiter, char *line)
{
	size_t	delim_len;

	delim_len = ft_strlen(delimiter);
	if (handle_heredoc_exit_conditions(line, delimiter))
		return (1);
	if (check_delimiter_match(line, delimiter, delim_len))
		return (1);
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
	free(line);
	return (0);
}

t_heredoc_ctx	*get_heredoc_ctx(t_cleanup *cleanup, char *filename)
{
	static t_heredoc_ctx	ctx;

	if (cleanup)
	{
		ctx.cleanup = cleanup;
		ctx.filename = filename;
	}
	return (&ctx);
}

void	do_heredoc_cleanup(void)
{
	t_heredoc_ctx	*ctx;

	ctx = get_heredoc_ctx(NULL, NULL);
	if (ctx->cleanup)
	{
		free_cmnd_ls(ctx->cleanup->cmnd_ls, ctx->cleanup->words);
		free(*(ctx->cleanup->raw_input));
		free_env_array(ctx->cleanup->env_array);
		free_env(ctx->cleanup->env);
		free(ctx->filename);
	}
}
