/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 07:01:12 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/03 19:00:27 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*new_node(char *env_name, char *env_value, bool export)
{
	t_env	*new;

	new = (t_env *)malloc (sizeof(t_env));
	new->env_name = env_name;
	new->env_value = env_value;
	new->is_exported = export;
	new->next = NULL;
	return (new);
}

t_env	*set_env(char **env)
{
	t_env	*head;
	t_env	*temp;
	char	**line;
	int		i;

	head = NULL;
	temp = NULL;
	i = 0;
	while (env[i])
	{
		line = ft_split(env[i], '=');
		if (!head)
		{
			head = new_node(line[0], line[1], true);
			temp = head;
		}
		else
		{
			temp->next = new_node(line[0], line[1], true);
			temp = temp->next;
		}
		free(line);
		i++;
	}
	return (head);
}

void	add_var_status(t_env **env, int status)
{
	t_env	*head;
	t_env	*new;
	bool	new_var;

	head = *env;
	new_var = false;
	new = new_node("?", ft_itoa(status), false);
	while (head != NULL)
	{
		if (ft_strequal(head->env_name, "?") == 0)
		{
			free(head->env_value);
			head->env_value = ft_strdup(ft_itoa(status));
			new_var = true;
		}
		head = head->next;
	}
	if (new_var == false)
		ft_lstadd_back_env(env, new);
	else
		free(new);
}
