/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command_implementation.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/09/03 18:11:18 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_array_size(char **array)
{
	int	size;

	size = 0;
	while (array[size])
		size++;
	return (size);
}

char	**bubble_sort(char **array, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(array[j], array[j + 1]) > 0)
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (array);
}

int	only_export(char **input, char **array_env)
{
	char	**sorted_env;
	int		i;

	sorted_env = bubble_sort(array_env, get_array_size(array_env));
	if (!sorted_env)
		return (1);
	i = 0;
	while (sorted_env[i])
	{
		printf("declare -x %s\n", sorted_env[i]);
		i++;
	}
	free(sorted_env);
	return (0);
}
size_t	joined_array_len(char **str)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (str[i])
	{
		len += ft_strlen(str[i]);
		if (str[i + 1])
			len += 1; // for space
		i++;
	}
	return (len);
}

// The function expects a buffer of at least total_len+1 bytes
void	print_array_error(char **str)
{
	int	i;

	i = 0;
	printf("minishell: export: '");
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1] != NULL)
		{
			printf(" ");
		}
		i++;
	}
	printf("': not a valid identifier\n");
}
// Returns:
// 0 = just VAR (no '=' present)
// 1 = VAR= (equal sign present, value is empty)
// 2 = VAR=value (equal sign present, value is not empty)
int	check_export_form(const char *input)
{
    const char *eq = ft_strchr(input, '=');

    if (!eq)
        return 0; // just VAR
    else if (*(eq + 1) == '\0')
        return 1; // VAR=
    else
        return 2; // VAR=value
}
int only_var(char *input, t_env *env)
{
    t_env *tmp = env;
    t_env *new_node;

    while (tmp)
    {
        if (ft_strcmp(tmp->key, input) == 0)
            return (0);
        if (tmp->next == NULL)
            break;
        tmp = tmp->next;
    }
    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (1);
    new_node->key = ft_strdup(input);
    new_node->next = NULL;
    if (!env)
        env = new_node;
    else
        tmp->next = new_node;
    return (0);
}
char *input_parse_key_export(char *input)
{
    char *eq = ft_strchr(input, '=');
    if (!eq)
        return ft_strdup(input); // No '=' found, whole input is the key
    return ft_substr(input, 0, eq - input); // Copy from start up to '='
}

char *input_parse_value_export(char *input)
{
    char *eq = ft_strchr(input, '=');
    if (!eq)
        return NULL;         // No '=' found, no value
    return eq + 1;           // Points to value (may be empty string)
}

int var_and_value(char *input, t_env *env)
{
    t_env *tmp = env;
    t_env *new_node;

    while (tmp)
    {
        if (ft_strcmp(tmp->key, input) == 0)
            return (0);
        if (tmp->next == NULL)
            break;
        tmp = tmp->next;
    }
    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (1);
    new_node->key = input_parse_key_export(input);
    new_node->value = input_parse_value_export(input);
    new_node->next = NULL;
    if (!env)
        env = new_node;
    else
        tmp->next = new_node;
    return (0);
}

int var_and_equal(char *input, t_env *env)
{
	t_env *tmp = env;
    t_env *new_node;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, input) == 0)
            return (0);
        if (tmp->next == NULL)
            break;
        tmp = tmp->next;
    }
    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (1);
    new_node->key = ft_strdup(input);
    new_node->value = ft_strdup("");
    new_node->next = NULL;
    if (!env)
        env = new_node;
    else
        tmp->next = new_node;
    return (0);
}

int	one_var(char *input, t_env *env)
{
    int form = check_export_form(input);
    if (form == 0)
    {
        
        printf("export VAR: add VAR with empty value if not present\n");
		return (only_var(input, env));
    }
    else if (form == 1)
    {
        // export VAR=
        printf("export VAR=: set VAR to empty string (add or update)\n");
		return(var_and_equal(input, env));
    }
    else if (form == 2)
    {
        // export VAR=value
		
        printf("export VAR=value: add or update VAR with value\n");
		return(var_and_value(input, env));
    }
	return(0);
}

int	parsing_export(char **input, t_env *env)
{
	char	*var_name;
	char	*var_value;

	if (input[1][0] >= '0' && input[1][0] <= '9' || ft_strchr(input[1], '+')
		|| input[1][0] == '=')
	{
		print_array_error(input);
		return (1);
	}
	// if (input[2] != NULL)
	// {
	// 	several_var(input, env);
	// }
	else
	{
		return (one_var(input[1], env));
	}
	return (0);
}

int	export_command_implementation(char **input, t_env *env, char **array_env)
{
	int		i;
	t_env	*tmp;

	i = 1;
	if (input[i] == NULL)
	{
		return (only_export(input, array_env));
	}
	else if ((input[i] != NULL))
	{
		return (parsing_export(input, env));
	}
	return (0);
}
