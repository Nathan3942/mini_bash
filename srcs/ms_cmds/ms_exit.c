/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:41:27 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/12 20:04:02 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_env **env)
{
	if ((*env) != NULL)
	{
		free((*env)->env_name);
		free((*env)->env_value);
		free_env(&(*env)->next);
		free(*env);
		*env = NULL;
	}
	return ;
}

void	ms_exit(t_params *para, t_env **env, t_data **data, t_put *put)
{
	
	(*data)->exit = true;
	if (para != NULL && para->com != NULL && para->com[1] != NULL)
	{
		printf("EXIT\n");
		free_all(para, &put, data);
		free_env(env);
		exit(ft_atoi(para->com[1]));
	}
	else
	{
		printf("EXIT\n");
		free_all(para, &put, data);
		free_env(env);
		exit(EXIT_SUCCESS);
	}
	return ;
}
