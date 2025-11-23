/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implem_heredoc11.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/23 15:47:38 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	do_heredoc_cleanup();
	exit(130);
}

void	cleanup_child_and_exit(int exit_code)
{
	do_heredoc_cleanup();
	exit(exit_code);
}

void	setup_heredoc_child_signals(void)
{
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_child_loop(int fd, char *delimiter, t_cleanup *cleanup,
		char *filename)
{
	char	*line;

	get_heredoc_ctx(cleanup, filename);
	setup_heredoc_child_signals();
	while (1)
	{
		line = readline("> ");
		if (!line)
			cleanup_child_and_exit(0);
		if (process_heredoc_line(fd, delimiter, line))
			cleanup_child_and_exit(0);
	}
}

int	handle_heredoc_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		signal(SIGINT, handler_sig_int);
		return (1);
	}
	g_exit_status = 128 + sig;
	signal(SIGINT, handler_sig_int);
	return (1);
}
