/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command_implementation3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:42:50 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/23 15:51:16 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	standard_cd(char **input, t_env *env)
{
	char	*path;
	char	*expanded_path;
	int		result;

	path = input[1];
	expanded_path = expand_tilde_path(path, env);
	if (expanded_path == (char *)-1)
		return (1);
	if (expanded_path)
		path = expanded_path;
	result = execute_cd(path, env);
	if (expanded_path)
		free(expanded_path);
	return (result);
}

int	cd_command_implementation(char **input, t_env *env)
{
	int	i;

	i = 1;
	if (input[i] == NULL)
	{
		return (only_cd(env));
	}
	else if ((input[i] != NULL) && (input[i + 1] == NULL))
	{
		if (ft_strcmp(input[i], "-") == 0)
			return (previous_dir(env));
		else if (ft_strcmp(input[i], "~") == 0)
			return (only_cd(env));
		else
			return (standard_cd(input, env));
	}
	else
	{
		ft_fprintf(STDERR_FD, "cd: too many arguments\n");
		return (1);
	}
	return (0);
}
