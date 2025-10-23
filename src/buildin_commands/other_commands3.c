/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/23 20:37:50 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
