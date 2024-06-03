/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:48:37 by njeanbou          #+#    #+#             */
/*   Updated: 2024/05/29 14:41:20 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_env(t_env **env)
{
	t_env	*heade;

	heade = *env;
	printf("\n\nEnvironnement :\n");
	while (heade != NULL)
	{
		printf("%s=", heade->env_name);
		printf("%s\n", heade->env_value);
		heade = heade->next;
	}
	printf("\n\n\n");
}

static char	*change_pwd(t_env **env)
{
	char	*tmp;
	t_env	*head;
	char	*path;

	head = *env;
	tmp = recherche_env("PWD", env);
	printf("%s    tmp\n", tmp);
	while (head != NULL)
	{
		if (ft_strequal(head->env_name, "PWD") == 0)
		{

			path = getcwd(NULL, 0);
			printf("%s  %s    path\n", path, head->env_name);
			head->env_value = ft_strdup(path);
			free(path);
		}
		head = head->next;
	}
	return (tmp);
}

static void	change_oldpwd(char *tmp, t_env **env)
{
	t_env	*head;

	head = *env;
	while (head != NULL)
	{
		if (ft_strstrbool(head->env_name, "OLDPWD") == 0)
		{
			free(head->env_value);
			head->env_value = ft_strdup(tmp);
		}
		head = head->next;
	}
}

int	ms_cd(t_params *para, t_env **env)
{
	char	*tmp;
	char	*path;

	if (para->com[1] == NULL || para->com[1][0] == '~' &&
		para->com[1][1] == '\0')
		path = recherche_env("HOME", env);
	else if (para->com[1][0] == '-' && para->com[1][1] == '\0')
		path = "..";
	else
		path = para->com[1];
	if (chdir(path) == 0)
	{
		tmp = change_pwd(env);
		printf("%s    tmp2", tmp);
		change_oldpwd(tmp, env);
		ms_pwd();
		print_env(env);
		return (0);
	}
	return (-1);
}
