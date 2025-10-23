/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command_implementation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:50 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/23 20:31:57 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_with_numeric_error(char *arg)
{
	ft_printf("exit: %s: numeric argument required\n", arg);
	g_exit_status = 2;
	write_history(".minishell_history");
	rl_clear_history();
	exit(g_exit_status);
}

long long	parse_and_validate_exit_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	if (arg[i] == '\0')
		exit_with_numeric_error(arg);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			exit_with_numeric_error(arg);
		i++;
	}
	return ((long long)ft_atoi(arg));
}

int	exit_command_implementation(char **input, t_env **my_env, char **array_env)
{
	long long	val;

	ft_printf("Exiting minishell\n");
	if (input[1])
	{
		val = parse_and_validate_exit_arg(input[1]);
		if (input[2])
		{
			ft_printf("exit: too many arguments\n");
			g_exit_status = 1;
			return (1);
		}
		g_exit_status = (int)((val % 256 + 256) % 256);
	}
	write_history(".minishell_history");
	rl_clear_history();
	exit(g_exit_status);
}
