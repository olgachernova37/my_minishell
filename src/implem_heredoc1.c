/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implem_heredoc1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/20 20:32:29 by olcherno         ###   ########.fr       */
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

static int	process_heredoc_line(int fd, char *delimiter, char *line)
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

static t_heredoc_ctx	*get_heredoc_ctx(t_cleanup *cleanup, char *filename)
{
	static t_heredoc_ctx	ctx;

	if (cleanup)
	{
		ctx.cleanup = cleanup;
		ctx.filename = filename;
	}
	return (&ctx);
}

static void	do_heredoc_cleanup(void)
{
	t_heredoc_ctx	*ctx;

	ctx = get_heredoc_ctx(NULL, NULL);
	if (ctx->cleanup)
	{
		rl_clear_history();
		free_cmnd_ls(ctx->cleanup->cmnd_ls, ctx->cleanup->words);
		free(*(ctx->cleanup->raw_input));
		free_env_array(ctx->cleanup->env_array);
		free_env(ctx->cleanup->env);
		free(ctx->filename);
	}
}

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	do_heredoc_cleanup();
	exit(130);
}

static void	cleanup_child_and_exit(int exit_code)
{
	do_heredoc_cleanup();
	exit(exit_code);
}

static void	setup_heredoc_child_signals(void)
{
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	heredoc_child_loop(int fd, char *delimiter, t_cleanup *cleanup,
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

static int	handle_heredoc_sigint(int sig)
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

static int	handle_child_signaled(int status)
{
	int	sig;

	sig = WTERMSIG(status);
	return (handle_heredoc_sigint(sig));
}

static int	handle_child_exited(int status)
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

static int	wait_for_heredoc_child(pid_t pid)
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
