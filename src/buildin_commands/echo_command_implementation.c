/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command_implementation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:26:59 by olcherno          #+#    #+#             */
/*   Updated: 2025/08/18 17:59:27 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int dollar_expand(char **argv, char *word)
{
    ft_printf("dollar_expand: %s\n", word);
    ft_printf("dollar_expand: %s\n", argv[0]);
    
    return (0);
}

int echo_command_implementation(t_input *input)
{
    int	i;
	int	n_FLAG;
    
	n_FLAG = 0;
	i = 1;
	if (input->argv[i] && ft_strncmp(input->argv[1], "-n", 3) == 0)
	{
		n_FLAG = 1;
           
	}
    printf("%s", input->argv[2]);

    printf("here\n");
    // char *argv[] = {"echo", "-n", "ASD","ASD","ASD", NULL};
    // ft_printf("%s", argv[0]);
    // if (ft_strncmp(input->argv[1], "$", 2) == 0)
    // {
    //     return (dollar_expand(input->argv, input->word));
    // }

    // while (input->argv[i] != NULL)
    // {
    //     ft_printf("%s", input->argv[i]);
    //     if (input->argv[i + 1] != NULL)
    //         ft_printf(" ");
    //     i++;
    // }

    if (input->argv[i] == NULL && n_FLAG == 0)
    {
        ft_printf("\n");
    }
    return (0);
}
