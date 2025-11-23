/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implem_heredoc111.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/23 15:47:59 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_child_signaled(int status)
{
	int	sig;

	sig = WTERMSIG(status);
	return (handle_heredoc_sigint(sig));
}

int	handle_child_exited(int status)
{
	int	ex;

	ex = WEXITSTATUS(status);
	if (ex != 0)
	{
		g_exit_status = ex;
		signal(SIGINT, handler_sig_int);
		return (1);
	}
	signal(SIGINT, handler_sig_int);
	return (0);
}

int	wait_for_heredoc_child(pid_t pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	status = 0;
	while (waitpid(pid, &status, 0) == -1 && errno == EINTR)
		;
	if (WIFSIGNALED(status))
		return (handle_child_signaled(status));
	if (WIFEXITED(status))
		return (handle_child_exited(status));
	signal(SIGINT, handler_sig_int);
	return (0);
}

int	write_heredoc_content(int fd, char *delimiter, char *filename,
		t_cleanup *cleanup)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		heredoc_child_loop(fd, delimiter, cleanup, filename);
	else
		return (wait_for_heredoc_child(pid));
	return (0);
}
