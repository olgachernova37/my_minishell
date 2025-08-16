/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command_implementation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:26:59 by olcherno          #+#    #+#             */
/*   Updated: 2025/08/16 23:58:17 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void echo_command_implementation(char **input)
{
    char *message;
    int i;

    // Skip the "echo " part
    i = 5;
    while (input[i] == ' ')
        i++;
    if (input[1] == '\0')
    {
        ft_printf("\n");
        return;
    }
    if (input[1] == '-n')
    {
        i += 2;
        while (input[i] == ' ')
            i++;
    }
    message = &input[i];
    
    // Print the message
    ft_printf("%s\n", message);
    
    return (0);
}
