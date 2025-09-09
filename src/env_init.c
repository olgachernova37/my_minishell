/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:50:50 by olcherno          #+#    #+#             */
/*   Updated: 2025/09/04 16:57:44 by olcherno         ###   ########.fr       */
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
        if (tmp->key)
        {
            if (tmp->value)
                printf("%s=%s\n", tmp->key, tmp->value);
            else
                printf("%s\n", tmp->key);
        }
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
			new_node->key = ft_strdup(envp[i]);
			*equals_pos = '=';
			new_node->value = ft_strdup(equals_pos + 1);
		}
		else
		{
			new_node->key = ft_strdup(envp[i]);
			new_node->value = ft_strdup("");
		}
		if (!new_node->key || !new_node->value)
		{
			free(new_node->key);
			free(new_node->value);
			free(new_node);
			exit(1);
		}
		add_new_node(&envp_list, new_node);
		i++;
	}
	return (envp_list);
}
