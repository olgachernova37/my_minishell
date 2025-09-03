/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:50:50 by olcherno          #+#    #+#             */
/*   Updated: 2025/09/03 18:01:41 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

// func for tests

void	print_my_env(t_env *env)
{
    t_env *tmp = env;

    while (tmp != NULL)
    {
        printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}

void	add_new_node(t_env **list, t_env *new_node)
{
	t_env	*tmp;

	if (!list || !new_node)
		return ;
	if (*list == NULL)
		*list = new_node;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

t_env	*env_init(char **envp)
{
	t_env	*new_node;
	t_env	*envp_list;
	char	*equals_pos;
	int		i;
	
	i = 0;
	envp_list = NULL;
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			exit(1);
		new_node->next = NULL;
		equals_pos = strchr(envp[i], '=');
		if (equals_pos)
		{
			*equals_pos = '\0';
			new_node->key = strdup(envp[i]);
			*equals_pos = '=';
			new_node->value = strdup(equals_pos + 1);
		}
		else
		{
			new_node->key = strdup(envp[i]);
			new_node->value = strdup("");
		}
		add_new_node(&envp_list, new_node);
		i++;
	}
	return (envp_list);
}
