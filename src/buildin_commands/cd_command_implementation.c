/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command_implementation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:44 by olcherno          #+#    #+#             */
/*   Updated: 2025/08/30 20:59:05 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	only_cd(t_input *input, t_env *env)
{
	char	*path;
	t_env	*tmp;

	tmp = env;
	// printf("it`s only cd");
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "HOME") == 0)
		{
			path = tmp->value;
		}
		tmp = tmp->next;
	}
    // printf("%s", path);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("getcwd"); 


	return (0);
}
int previous_dir(t_input *input, t_env *env)
{
    	char	*path;
	t_env	*tmp;

	tmp = env;
	// printf("it`s only cd");
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			path = tmp->value;
		}
		tmp = tmp->next;
	}
    //printf("%s", path);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
}

int standard_cd(t_input *input)
{
    char	*path;
    path = input->argv[1];
    
    if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
        char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("getcwd"); 
    return(0);
}

int	cd_command_implementation(t_input *input, t_env *env)
{
	int	i;

	i = 1;
	if (input->argv[i] == NULL)
	{
		return (only_cd(input, env));
	}
	else if ((input->argv[i] != NULL) && (input->argv[i + 1] == NULL))
	{   
        if(ft_strcmp(input->argv,"-") == 0)
            return(previous_dir(input, env));
        else
        {
            return (standard_cd(input));
        }
	}
	else
	{
		printf("cd: too many arguments\n");
		return (1);
	}

    
	return (0);

}
