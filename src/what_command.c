/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/09/09 22:44:48 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Define the global variable

//WRONG LOGIC !!!

bool	is_command_buildin(char **input)
{
	t_input	*f_token;

	if (ft_strncmp(input[0], "cd", 2) == 0)
		return (true);
	else if (ft_strncmp(input[0], "pwd", 3) == 0)
		return (true);
	else if (ft_strncmp(input[0], "export", 6) == 0)
		return (true);
	else if (ft_strncmp(input[0], "unset", 5) == 0)
		return (true);
	else if (ft_strncmp(input[0], "echo", 4) == 0)
		return (true);
	else if (ft_strncmp(input[0], "env", 3) == 0)
		return (true);
	else if (ft_strncmp(input[0], "exit", 4) == 0)
		return (true);
	else
		return (false);
}

void	which_buildin_command(char **input, t_env **my_env, char **array_env)
{
	if (ft_strncmp(input[0], "echo", 4) == 0)
		exit_status = echo_command_implementation(input, my_env);
	else if (ft_strncmp(input[0], "pwd", 3) == 0)
		exit_status = pwd_command_implementation(*my_env);
	else if (ft_strncmp(input[0], "export", 6) == 0)
		exit_status = export_command_implementation(input, my_env, array_env);
	else if (ft_strncmp(input[0], "unset", 5) == 0)
		exit_status = unset_command_implementation(my_env, input);
	else if (ft_strncmp(input[0], "cd", 2) == 0)
		exit_status = cd_command_implementation(input, *my_env);
	// else if (ft_strncmp(input[0], "exit", 4) == 0)
	// exit_command_implementation(my_env);
	else if (ft_strncmp(input[0], "env", 3) == 0)
	{
		print_my_env(*my_env);
		exit_status = 0;
	}
	else if (ft_strncmp(input[0], "exit", 4) == 0)
		exit_status = exit_command_implementation(*my_env);
}

void	what_command(char **input, t_env **my_env, char **array_env)
{
	if (is_command_buildin(input))
		which_buildin_command(input, my_env, array_env);
	else
		exit_status = other_commands_implementation(input, my_env);
}
