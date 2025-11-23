/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command_implementation2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:42:50 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/23 15:51:03 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env_value(t_env *env, const char *key, const char *new_value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_value);
			break ;
		}
		tmp = tmp->next;
	}
}

int	change_to_oldpwd(char *path, char *prev_dir, char *cwd)
{
	if (!getcwd(prev_dir, PATH_MAX))
		return (perror("getcwd"), 1);
	if (chdir(path) == -1)
		return (perror("cd"), 1);
	if (getcwd(cwd, PATH_MAX))
		printf("%s\n", cwd);
	else
		perror("getcwd");
	return (0);
}

int	previous_dir(t_env *env)
{
	char	*path;
	char	cwd[PATH_MAX];
	char	prev_dir[PATH_MAX];

	path = get_env_value(env, "OLDPWD");
	if (!path || !*path)
		return (printf("cd: OLDPWD not set\n"), 1);
	if (change_to_oldpwd(path, prev_dir, cwd) != 0)
		return (1);
	update_env_value(env, "OLDPWD", prev_dir);
	update_env_value(env, "PWD", cwd);
	return (0);
}

char	*expand_tilde_path(char *path, t_env *env)
{
	char	*home;
	char	*expanded;

	if (path[0] != '~')
		return (NULL);
	home = get_env_value(env, "HOME");
	if (!home)
	{
		ft_fprintf(STDERR_FD, "cd: HOME not set\n");
		return ((char *)-1);
	}
	if (path[1] == '\0')
		expanded = ft_strdup(home);
	else if (path[1] == '/')
		expanded = ft_strjoin(home, path + 1);
	else
		expanded = ft_strdup(path);
	return (expanded);
}

int	execute_cd(char *path, t_env *env)
{
	change_oldpwd(env);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	change_pwd(env);
	return (0);
}
