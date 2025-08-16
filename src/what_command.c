/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 21:59:13 by olcherno          #+#    #+#             */
/*   Updated: 2025/08/16 23:15:13 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_command_buildin(char *input)
{
	if ((ft_strncmp(input, "cd", 2) == 0) || (ft_strncmp(input, "pwd", 3) == 0))
	{
		return (true);
	}
	else if (ft_strncmp(input, "export", 6) == 0)
	{
        return (true);
	}
    else if (ft_strncmp(input, "unset",5) == 0)
    {
        return (true);
    }
    else if ((ft_strncmp(input, "echo", 4) == 0) || (ft_strncmp(input, "env", 3) == 0))
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

void	which_buildin_command(char *input, t_env *my_env)
{
	// if (ft_strncmp(input, "echo", 4) == 0)
	// 	echo_command_implementation(input);
	// else if (ft_strncmp(input, "pwd", 3) == 0)
	// 	pwd_command_implementation();
	// else if (ft_strncmp(input, "export", 6) == 0)
	// 	export_command_implementation(my_env);
	// else if (ft_strncmp(input, "unset", 5) == 0)
	// 	unset_command_implementation(my_env);
	// else if (ft_strncmp(input, "cd", 2) == 0)
	// 	cd_command_implementation(my_env);
	// else if (ft_strncmp(input, "exit", 4) == 0)
	// 	exit_command_implementation(my_env);
	// else if (ft_strncmp(input, "env", 3) == 0)
	// 	print_my_env(my_env);
    ft_printf("which_buildin_command: %s\n", input);
}

void	what_command(char *input, t_env *my_env)
{
	if (is_command_buildin(input))
	{
		which_buildin_command(input, my_env);
	}
	//   else
	//   {
	//     char *cmd[] = {input, NULL};
	//     execve(input, cmd, my_env);
		// Execute the command with the environment
	//     perror("execve"); // Print error if execve fails
	//   }
}
