/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 04:41:08 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/04 14:38:13 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_var_beg(t_params **para, t_env **env)
{
	t_params	*headp;
	char		*var;
	int			i;

	var = NULL;
	headp = *para;
	i = 0;
	while (headp->com[i] != NULL)
	{	
		if (headp->com[i][0] == '$')
		{
			var = recherche_env(headp->com[i], env);
			if (var[0] == ';' && ft_strlen(var) == 1)
				var = "";
			if (var != NULL)
			{
				free(headp->com[i]);
				headp->com[i] = ft_strdup(var);
			}
		}
		i++;
	}
}

static char	**mid_var_env(char **split_str, t_env **env)
{
	int		i;
	char	*var;

	i = 0;
	while (split_str[i] != NULL)
	{
		if (split_str[i][0] == '$')
		{
			var = recherche_env(split_str[i], env);
			if (var != NULL)
			{
				free(split_str[i]);
				split_str[i] = ft_strdup(var);
			}
		}
		i++;
	}
	split_str[i] = NULL;
	return (split_str);
}

static char	*mid_var(char *str, t_env **env)
{
	char	**split_str;
	char	*var;
	int		i;

	split_str = split_var(str);
	split_str = mid_var_env(split_str, env);
	i = 0;
	var = NULL;
	while (split_str[i] != NULL)
	{
		var = ft_strjoin(var, split_str[i]);
		i++;
	}
	var = clean_var(var);
	return (var);
}

static void	set_var_mid(t_params **para, t_env **env)
{
	char		*var;
	int			i;
	int			z;

	var = NULL;
	i = 0;
	while ((*para)->com[i] != NULL)
	{
		if ((*para)->com[i][0] == '\'')
			break ;
		z = 0;
		while ((*para)->com[i][z] != '\0')
		{
			if ((*para)->com[i][z] == '$')
			{
				var = mid_var((*para)->com[i], env);
				free((*para)->com[i]);
				(*para)->com[i] = var;
				break ;
			}
			z++;
		}
		i++;
	}
}

void	set_var(t_params **para, t_env **env)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while ((*para)->com[i] != NULL)
	{
		if ((*para)->com[i][z] == '\'')
			break ;
		i++;
	}
	set_var_mid(para, env);
}
