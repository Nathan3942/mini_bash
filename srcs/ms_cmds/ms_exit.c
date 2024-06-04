/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:41:27 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/04 14:27:25 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_env **env)
{
	if ((*env) != NULL)
	{
		// free((*env)->env_name);
		// free((*env)->env_value);
		free_env(&(*env)->next);
		free(*env);
		*env = NULL;
	}
	return ;
}

void	ms_exit(t_params *para, t_put *put, t_env **env, t_data **data)
{
	printf("EXIT\n");
	(*data)->exit = true;
	if (para != NULL && para->com != NULL && para->com[1] != NULL)
	{
		//free_all(&para, &put);
		free_env(env);
		exit(ft_atoi(para->com[1]));
	}
	else
	{
		//free_all(&para, &put);
		free_env(env);
		exit(EXIT_SUCCESS);
	}
	return ;
}
