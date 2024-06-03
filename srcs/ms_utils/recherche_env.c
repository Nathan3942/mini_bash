/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recherche_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 04:52:22 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/03 18:55:52 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*recherche_env(char *str, t_env **env)
{
	t_env	*head;

	head = *env;
	while (head != NULL && str != NULL)
	{
		if (ft_strequal(head->env_name, str + 1) == 0)
		{
			printf("%s\n", head->env_name);
			return (head->env_value);
		}
		head = head->next;
	}
	return (";\0");
}

char	*clean_var(char *var)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = 0;
	while (var[i] != '\0')
	{
		if (var[i] != ';')
			len++;
		i++;
	}
	new = (char *)malloc ((len + 1) * sizeof(char));
	i = 0;
	len = 0;
	while (var[i] != '\0')
	{
		if (var[i] != ';')
			new[len++] = var[i];
		i++;
	}
	new[len] = '\0';
	return (new);
}
