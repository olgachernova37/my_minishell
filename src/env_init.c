/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:50:50 by olcherno          #+#    #+#             */
/*   Updated: 2025/07/28 19:34:30 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

void	print_my_env(t_env *env) // Function to print the environment variables
{
	t_env *current = env;
	while (current)
	{
		if (current->value)
			ft_printf("%s=%s\n", current->key, current->value);
		else
			ft_printf("%s=\n", current->key);
		current = current->next;
	}
}

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	char	*equals_pos;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			exit(1); // handle memory allocation error
		equals_pos = strchr(envp[i], '=');
		if (equals_pos)
		{
			*equals_pos = '\0'; // temporarily null-terminate
			new_node->key = ft_strdup(envp[i]);
			new_node->value = ft_strdup(equals_pos + 1);
			*equals_pos = '='; // restore original string
		}
		else
		{
			new_node->key = ft_strdup(envp[i]);
			new_node->value = ft_strdup("");
		}
		new_node->next = env_list;
		env_list = new_node;
		i++;
	}
	return (env_list);
}
