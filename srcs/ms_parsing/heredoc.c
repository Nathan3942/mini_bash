/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 04:04:52 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/14 14:42:14 by vboxuser         ###   ########.fr       */
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

static char	*update_doctmp(char *doc, char **doctmp, t_env **env)
{
	char	*docbis;
	char	*var_tmp;
	
	docbis = NULL;
	if (ft_strstr(doc, "$") != NULL)
	{
		var_tmp = ft_strdup(doc);
		free(doc);
		doc = mid_var(var_tmp, env);
		free(var_tmp);
	}
	if (ft_strequal(*doctmp, "") == 0)
	{
		free(*doctmp);
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
	return (*doctmp);
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
