/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/20 18:12:07 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*get_path_from_env(t_env **env)
{
	while (*env)
	{
		if (ft_strncmp((*env)->key, "PATH", ft_strlen("PATH")) == 0)
			return ((*env)->value);
		env = &((*env)->next);
	}
	return (NULL);
}

char	**input_with_null_terminator(char **input)
{
	int		i;
	char	**new_input;

	i = 0;
	while (input[i])
		i++;
	new_input = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (input[i])
	{
		new_input[i] = ft_strdup(input[i]);
		i++;
	}
	new_input[i] = NULL;
	new_input[i + 1] = NULL;
	return (new_input);
}

char	**init_path_components(char **input, t_env **env)
{
	char	**splited_path;
	char	*path_value;

	path_value = get_path_from_env(env);
	if (!path_value)
		return (NULL);
	splited_path = ft_split(path_value, ':');
	if (!splited_path || !*splited_path)
	{
		if (splited_path)
			free_split(splited_path);
		return (NULL);
	}
	return (splited_path);
}

char	*try_command_in_dirs(char **splited_path, char *input_command)
{
	char	*path_with_command;
	int		i;

	i = 0;
	while (splited_path[i])
	{
		path_with_command = ft_strjoin(splited_path[i], input_command);
		if (access(path_with_command, X_OK) == 0)
		{
			return (path_with_command);
		}
		free(path_with_command);
		i++;
	}
	return (NULL);
}
