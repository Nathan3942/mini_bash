/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:03:09 by njeanbou          #+#    #+#             */
/*   Updated: 2024/05/28 14:31:14 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	unset_var(char *str, t_env **env)
{
	t_env	*head;
	t_env	*pre;

	head = *env;
	pre = NULL;
	while (head != NULL && ft_strequal(head->env_name, str) != 0)
	{
		pre = head;
		head = head->next;
	}
	pre->next = head->next;
	free(head);
	return (EXIT_SUCCESS);
}

int	ms_unset(t_params *para, t_env **env)
{
	int	i;

	i = 1;
	if (para->com[1] == NULL)
		return (EXIT_SUCCESS);
	if (para->com[1] != NULL)
	{
		while (para->com[i] != NULL)
		{
			unset_var(para->com[i], env);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
