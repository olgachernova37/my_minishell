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

char *get_path_from_env(t_env **env)
{
    while (*env)
    {
        if (ft_strncmp((*env)->key, "PATH", ft_strlen("PATH")) == 0)
            return ((*env)->value);
        env = &((*env)->next);
    }
    return (NULL);
}



int other_commands_implementation(char **input, t_env **env)
{
    char **splited_path;
    char *path_value = get_path_from_env(env);
   // printf("PATH value: %s\n", path_value);

    splited_path = ft_split(path_value, ':');
    // while (*splited_path)
    // {
    //     printf("SPLITED PATH: %s\n", *splited_path);
    //     splited_path++;
    // }

    if (!*splited_path)
        return (1);
    int i = 0;
    char *input_command = ft_strjoin(input[0], "/");
    printf("INPUT COMMAND: %s\n", input_command);
    // while (splited_path[i])
    // {
    //     char *path_with_command = ft_strjoin(splited_path[i], 
    // }
}