/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:10:28 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/13 14:00:18 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_export(t_env **env)
{
	t_env	*head;

	head = *env;
	while (head != NULL)
	{
		if (head->is_exported == true && head->env_value != NULL)
			printf("declare -x %s=\"%s\"\n", head->env_name, head->env_value);
		else if (head->is_exported == true && head->env_value == NULL)
			printf("declare -x %s\n", head->env_name);
		head = head->next;
	}
	return (EXIT_SUCCESS);
}

static void	mod_var(t_env *head, char **line, bool *new_var)
{
	while (head != NULL)
	{
		if (ft_strequal(head->env_name, line[0]) == 0
			&& head->is_exported == true)
		{
			free(head->env_value);
			head->env_value = ft_strdup(line[1]);
			(*new_var) = true;
		}
		if (ft_strequal(head->env_name, line[0]) == 0
			&& head->is_exported == false)
		{
			head->is_exported = true;
			(*new_var) = true;
		}
		head = head->next;
	}
}

static int	add_export(char *var, t_env **env)
{
	t_env	*new;
	t_env	*head;
	char	**line;
	bool	new_var;

	head = *env;
	new_var = false;
	line = ft_split(var, '=');
	new = new_node(line[0], line[1], true);
	mod_var(head, line, &new_var);
	ft_free_tab(line);
	if (new_var == false)
		ft_lstadd_back_env(env, new);
	return (EXIT_SUCCESS);
}

int	ms_export(t_params *para, t_env **env)
{
	int	i;

	i = 1;
	if (para->com[1] == NULL)
		return (print_export(env));
	else if (para->com[1] != NULL)
	{
		while (para->com[i] != NULL)
		{
			add_export(para->com[i], env);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
