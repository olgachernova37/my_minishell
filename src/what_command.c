/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:45:07 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/24 00:00:00 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	match_buildin(char *og_input, char *match_cmnd)
{
	while (*og_input == *match_cmnd && *match_cmnd)
	{
		og_input++;
		match_cmnd++;
	}
	if (!(*match_cmnd) && !(*og_input))
		return (1);
	return (0);
}

bool	is_command_buildin(char **input)
{
	t_input	*f_token;

	if (match_buildin(input[0], "cd"))
	{
		return (true);
	}
	else if (match_buildin(input[0], "pwd"))
		return (true);
	else if (match_buildin(input[0], "export"))
		return (true);
	else if (match_buildin(input[0], "unset"))
		return (true);
	else if (match_buildin(input[0], "echo"))
		return (true);
	else if (match_buildin(input[0], "env"))
		return (true);
	else if (match_buildin(input[0], "exit"))
		return (true);
	else
		return (false);
}

int	which_buildin_command(t_cmnd *cmnd, t_env **my_env, char **array_env)
{
	if (match_buildin(cmnd->full_argv[0], "echo"))
		return (echo_command_implementation(&cmnd, my_env));
	else if (match_buildin(cmnd->argv[0], "pwd"))
		return (pwd_command_implementation(*my_env));
	else if (match_buildin(cmnd->argv[0], "export"))
		return (export_command_implementation(cmnd->argv, my_env, array_env));
	else if (match_buildin(cmnd->argv[0], "unset"))
		return (unset_command_implementation(my_env, cmnd->argv));
	else if (match_buildin(cmnd->argv[0], "cd"))
		return (cd_command_implementation(cmnd->argv, *my_env));
	else if (match_buildin(cmnd->argv[0], "exit"))
		return (exit_command_implementation(cmnd->argv, my_env, array_env));
	else if (match_buildin(cmnd->argv[0], "env"))
	{
		print_my_env(*my_env);
		return (0);
	}
	return (0);
}

void	what_command(t_cmnd **cmnd_ls, t_env **my_env, char **array_env)
{
	t_cmnd	*cmnd;
	int		stdin_backup;
	int		stdout_backup;

	cmnd = *cmnd_ls;
	while (cmnd != NULL)
	{
		// Зберегти оригінальні stdin/stdout
		stdin_backup = dup(STDIN_FILENO);
		stdout_backup = dup(STDOUT_FILENO);
		// Застосувати перенаправлення
		if (implamentation_redir(cmnd) != 0)
		{
			// Відновити stdin/stdout при помилці
			dup2(stdin_backup, STDIN_FILENO);
			dup2(stdout_backup, STDOUT_FILENO);
			close(stdin_backup);
			close(stdout_backup);
			g_exit_status = 1;
			cmnd = cmnd->next;
			continue ;
		}
		// Виконати команду (builtin або зовнішню)
		if (is_command_buildin(cmnd->argv))
			g_exit_status = which_buildin_command(cmnd, my_env, array_env);
		else
			g_exit_status = other_commands_implementation(cmnd->argv, my_env);
		// Відновити оригінальні stdin/stdout
		dup2(stdin_backup, STDIN_FILENO);
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdin_backup);
		close(stdout_backup);
		cmnd = cmnd->next;
	}
}
