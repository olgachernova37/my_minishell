/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/24 00:00:00 by olcherno         ###   ########.fr       */
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

int	execute_command(char *path_with_command, char **input)
{
    char	**new_input;
    pid_t	pid;
    int		status;

    new_input = input_with_null_terminator(input);
    if (!new_input)
        return (1);
    pid = fork();
    if (pid == 0)
    {
        setup_child_signals();
        execve(path_with_command, new_input, NULL);
        perror("execve");
        free_split(new_input);
        exit(127);
    }
    else if (pid > 0)
    {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        waitpid(pid, &status, 0);
        signal(SIGINT, handler_sig_int);
        signal(SIGQUIT, SIG_IGN);
        free_split(new_input);
        return (handle_child_exit(status));
    }
    perror("fork");
    free_split(new_input);
    return (1);
}

int	handle_direct_path_command(char **input)
{
	int	i;

	if (access(input[0], X_OK) == 0)
	{
		i = execute_command(input[0], input);
		return (i);
	}
	else
	{
		perror(input[0]);
		return (127);
	}
}

int	handle_path_command(char **input, t_env **env)
{
	char	*path_with_command;
	int		i;

	path_with_command = find_command_path(input, env);
	if (path_with_command)
	{
		i = execute_command(path_with_command, input);
		free(path_with_command);
		return (i);
	}
	else
	{
		fprintf(stderr, "bash: %s: command not found\n", input[0]);
		return (127);
	}
}

int	other_commands_implementation(char **input, t_env **env)
{
	if (!input || !input[0])
		return (0);
	if (ft_strchr(input[0], '/'))
		return (handle_direct_path_command(input));
	else
		return (handle_path_command(input, env));
}
