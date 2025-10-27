/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/27 20:20:59 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static int	handle_child_exit(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			return (130);
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			write(1, "Quit (core dumped)\n", 19);
			return (131);
		}
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	execute_child_process(char *path_with_command, char **new_input)
{
	setup_child_signals();
	execve(path_with_command, new_input, NULL);
	perror("execve");
	free_split(new_input);
	exit(127);
}

int	wait_for_child(pid_t pid, char **new_input)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handler_sig_int);
	signal(SIGQUIT, SIG_IGN);
	free_split(new_input);
	return (handle_child_exit(status));
}

int	execute_command(char *path_with_command, char **input)
{
	char	**new_input;
	pid_t	pid;

	new_input = input_with_null_terminator(input);
	if (!new_input)
		return (1);
	pid = fork();
	if (pid == 0)
		execute_child_process(path_with_command, new_input);
	else if (pid > 0)
		return (wait_for_child(pid, new_input));
	perror("fork");
	free_split(new_input);
	return (1);
}
