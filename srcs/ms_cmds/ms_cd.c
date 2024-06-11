/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:48:37 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/11 14:50:55 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	print_env(t_env **env)
// {
// 	t_env	*heade;

// 	heade = *env;
// 	printf("\n\nEnvironnement :\n");
// 	while (heade != NULL)
// 	{
// 		printf("%s=", heade->env_name);
// 		printf("%s\n", heade->env_value);
// 		heade = heade->next;
// 	}
// 	printf("\n\n\n");
// }

static char	*change_pwd(t_env **env)
{
	char	*tmp;
	t_env	*head;
	char	*path;

	head = *env;
	tmp = recherche_env("$PWD", env);
	//printf("%s    tmp\n", tmp);
	while (head != NULL)
	{
		if (ft_strequal(head->env_name, "PWD") == 0)
		{

			path = getcwd(NULL, 0);
			//printf("%s  %s    path\n", path, head->env_name);
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

char	*set_path(char **com, t_env **env)
{
	char	*path;

	if (com[1] == NULL)
		path = recherche_env("$HOME", env);
	else if (com[1][0] == '~')
	{
		if (com[1][1] == '\0')
			path = recherche_env("$HOME", env);
		else
			path = ft_strjoin(recherche_env("$HOME", env), com[1] + 1);
	}
	else if (com[1][0] == '-' && com[1][1] == '\0')
		path = recherche_env("$OLDPWD", env);
	else
		path = com[1];
	return (path);
}

int	ms_cd(t_params *para, t_env **env)
{
	char	*tmp;
	char	*path;

	path = set_path(para->com, env);
	if (access(path, F_OK) != 0)
		printf("minishell: cd: %s: No such file or directory\n", path);
	if (chdir(path) == 0)
	{
		tmp = change_pwd(env);
		change_oldpwd(tmp, env);
		if (para->com[1] != NULL)
		{
			if (para->com[1][0] == '-' && para->com[1][1] == '\0')
				ms_pwd();
		}
		return (0);
	}
	return (-1);
}
