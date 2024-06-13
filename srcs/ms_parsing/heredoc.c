/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 04:04:52 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/13 16:54:49 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup_nl(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1) + 2;
	dup = (char *) malloc(len * sizeof(*s1));
	i = 0;
	if (dup == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i++] = '\n';
	dup[i] = '\0';
	return (dup);
}

// static char	*heredoc(char *exit, t_env **env)
// {
// 	char	*doctmp;
// 	char	*res;
// 	char	*doc;

// 	doctmp = ft_strdup("");  // Initialiser doctmp avec une chaîne vide pour éviter les problèmes de concaténation
// 	res = NULL;
// 	while (1)
// 	{
// 		doc = readline("heredoc> ");
// 		if (!doc)
// 		{
// 			free(doctmp);
// 			return (res);
// 		}
// 		if (ft_strequal(doc, exit) == 0)
// 		{
// 			free(doc);
// 			if (*doctmp == '\0')  // Vérifier si doctmp est vide
// 			{
// 				free(doctmp);
// 				return (res);
// 			}
// 			res = ft_strdup_nl(doctmp);
// 			free(doctmp);
// 			break;
// 		}
// 		if (ft_strstr(doc, "$") != NULL)
// 		{
// 			char *expanded_doc = mid_var(doc, env);
// 			free(doc);
// 			doc = expanded_doc;
// 		}
// 		char *tmp = doctmp;
// 		doctmp = ft_strjoin_c(doctmp, doc, '\n');
// 		free(tmp);
// 		free(doc);
// 	}
// 	return (res);
// }


static char	*heredoc(char *exit, t_env **env)
{
	char	*doctmp;
	char	*res;
	char	*doc;

	doctmp = ft_strdup("");
	res = NULL;
	while (1)
	{
		doc = readline("heredoc> ");
		if (ft_strequal(doc, exit) == 0)
		{
			free(doc);
			if (doctmp == NULL)
				return (res);
			res = ft_strdup_nl(doctmp);
			free(doctmp);
			break ;
		}
		if (ft_strstr(doc, "$") != NULL)
			doc = mid_var(doc, env);
		if (ft_strequal(doctmp, "") == 0)
			doctmp = ft_strdup(doc);
		else
			doctmp = ft_strjoin_c(doctmp, doc, '\n');
		free(doc);
	}
	return (res);
}

void	ft_doc(t_params **para, t_env **env, t_put **put)
{
	t_params	*head;
	char		*tmp;
	int			i;
	char		*exit;

	i = 0;
	head = *para;
	exit = NULL;
	if (head->inp_red == entre2)
	{	
		while (head->com[i] != NULL)
		{
			if (head->com[i][0] == '<')
				exit = head->com[i + 1];
			i++;
		}
		(*put)->input = ft_strdup(exit);
		tmp = heredoc(exit, env);
		i = open(exit, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (tmp != NULL)
			ft_putstr_fd(tmp, i);
		free(tmp);
	}
}
