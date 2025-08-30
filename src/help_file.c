/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:50:05 by olcherno          #+#    #+#             */
/*   Updated: 2025/08/30 21:40:04 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_input *initialize_command()
{
    t_input *cmd = malloc(sizeof(t_input));
    if (!cmd)
        return NULL;

    cmd->type = TOKEN_WORD;
    cmd->next = NULL;
    cmd->word = "ls";

    // Dynamically allocate memory for argv
    cmd->argv = malloc(sizeof(char *) * 6); // 5 arguments + NULL terminator
    if (!cmd->argv)
    {
        free(cmd);
        return NULL;
    }



    cmd->argv[0] = ft_strdup("ls");
    cmd->argv[2] = NULL;



    // cmd->argv[0] = ft_strdup("cd");
    // cmd->argv[1] = ft_strdup("..");
    // cmd->argv[2] = NULL;

    
    // cmd->argv[0] = ft_strdup("cd");
    // cmd->argv[1] = ft_strdup("/home/olcherno/Workplace/minishell/my_minishell/libs");
    // cmd->argv[2] = NULL;
    
    
    // cmd->argv[0] = ft_strdup("cd");
    // cmd->argv[1] = ft_strdup("libs");
    // cmd->argv[2] = ft_strdup("ASD");
    // cmd->argv[4] = NULL;
   
   
    // cmd->argv[0] = ft_strdup("cd");
    // cmd->argv[1] = ft_strdup("libs");
    // cmd->argv[2] = ft_strdup("ASD");
    // cmd->argv[4] = NULL;

    // cmd->argv[0] = ft_strdup("echo");
    // cmd->argv[1] = ft_strdup("ASD");
    // cmd->argv[2] = ft_strdup("ASD");
    // cmd->argv[3] = ft_strdup("ASDuuiy");
    // cmd->argv[4] = NULL;

    // cmd->argv[0] = ft_strdup("echo");
    // cmd->argv[1] = ft_strdup("-n");
    // cmd->argv[2] = ft_strdup("ASD");
    // cmd->argv[3] = ft_strdup("ASD");
    // cmd->argv[4] = ft_strdup("ASD");
    // cmd->argv[5] = NULL;

    return cmd;
}