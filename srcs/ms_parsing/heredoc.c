/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 04:04:52 by njeanbou          #+#    #+#             */
/*   Updated: 2024/07/02 17:22:06 by njeanbou         ###   ########.fr       */
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

static void	update_doctmp(char *doc, char **doctmp, t_env **env)
{
	char	*docbis;

	if (ft_strstr(doc, "$") != NULL)
	{
		docbis = ft_strdup(doc);
		free(doc);
		doc = mid_var(docbis, env);
		free(docbis);
	}
	if (ft_strequal(*doctmp, "") == 0)
	{
		free(*doctmp);
		if (ft_strequal(doc, "\0") == 0)
			*doctmp = ft_strdup(" ");
		else
			*doctmp = ft_strdup(doc);
	}
	else
	{
		docbis = ft_strdup(*doctmp);
		free(*doctmp);
		*doctmp = ft_strjoin_c(docbis, doc, '\n');
		free(docbis);
	}
	free(doc);
}

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
		if (doc == NULL)
			return (NULL);
		if (ft_strequal(doc, exit) == 0)
		{
			free(doc);
			if (doctmp == NULL)
				return (res);
			res = ft_strdup_nl(doctmp);
			free(doctmp);
			break ;
		}
		update_doctmp(doc, &doctmp, env);
	}
	return (res);
}

void	ft_doc(t_params **para, t_env **env, t_put **put)
{
	t_params	*head;
	char		*tmp;
	int			i;
	char		*exit_wd;

	i = 0;
	head = *para;
	exit_wd = NULL;
	if (head->inp_red == entre2)
	{
		while (head->com[i] != NULL)
		{
			if (head->com[i][0] == '<')
				exit_wd = head->com[i + 1];
			i++;
		}
		(*put)->input = ft_strdup(exit_wd);
		tmp = heredoc(exit_wd, env);
		i = open(exit_wd, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (tmp != NULL)
			ft_putstr_fd(tmp, i);
		free(tmp);
	}
}
