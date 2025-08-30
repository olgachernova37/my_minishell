/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:27:45 by olcherno          #+#    #+#             */
/*   Updated: 2025/08/30 21:42:37 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int other_commands_implementation(t_input *input, t_env *env)
{

	//    ;
	//     perror("execve"); // Print error if execve fails
    

    execve(input->word, input->argv, envp);
     printf("it`s only ls\n");
    // if ( execve(input->word, input->argv, env) != 0)
    //     return(1);
    return 0;
}