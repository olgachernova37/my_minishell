/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 21:59:13 by olcherno          #+#    #+#             */
/*   Updated: 2025/08/30 21:35:00 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_command_buildin(t_input *input)
{
	if ((ft_strncmp(input->word, "cd", 2) == 0) || (ft_strncmp(input->word, "pwd", 3) == 0))
	{
		return (true);
	}
	else if (ft_strncmp(input->word, "export", 6) == 0)
	{
        return (true);
	}
    else if (ft_strncmp(input->word, "unset",5) == 0)
    {
        return (true);
    }
    else if ((ft_strncmp(input->word, "echo", 4) == 0) || (ft_strncmp(input->word, "env", 3) == 0))
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

void	which_buildin_command(t_input *input, t_env *my_env)
{
	int exit_status;

	if (ft_strncmp(input->word, "echo", 4) == 0)
		exit_status = echo_command_implementation(input);

	
	else if (ft_strncmp(input->word, "pwd", 3) == 0)
		exit_status = pwd_command_implementation(input, my_env);
	// else if (ft_strncmp(input->word, "export", 6) == 0)
	// 	export_command_implementation(my_env);
	// else if (ft_strncmp(input->word, "unset", 5) == 0)
	// 	unset_command_implementation(my_env);
	else if (ft_strncmp(input->word, "cd", 2) == 0)
		exit_status = cd_command_implementation(input, my_env);
	// else if (ft_strncmp(input->word, "exit", 4) == 0)
	// 	exit_command_implementation(my_env);
	else if (ft_strncmp(input->word, "env", 3) == 0)
		print_my_env(my_env);
    //ft_printf("which_buildin_command: %s\n", input->word);
	// ft_printf("exit_status: %d\n", exit_status);
}

void	what_command(t_input *input, t_env *my_env)
{
	int exit_status;

	if (is_command_buildin(input))
	{
		which_buildin_command(input, my_env);
	}
	  else
	  {
		exit_status = other_commands_implementation(input, my_env);
	  }
}
