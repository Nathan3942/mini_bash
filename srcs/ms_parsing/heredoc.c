/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 04:04:52 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/07 15:24:47 by njeanbou         ###   ########.fr       */
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

static char	*heredoc(char *exit, t_env **env)
{
	char	*doctmp;
	char	*res;
	char	*doc;

	doctmp = NULL;
	res = NULL;
	while (1)
	{
		doc = readline("heredoc> ");
		if (ft_strequal(doc, exit) == 0)
		{
			if (doctmp == NULL)
				return (res);
			res = ft_strdup_nl(doctmp);
			res = mid_var(res, env);
			free(doctmp);
			break ;
		}
		doctmp = ft_strjoin_c(doctmp, doc, '\n');

	}
	return (res);
}

void	ft_doc(t_params **para, t_env **env)
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
		tmp = heredoc(exit, env);
		if (tmp == NULL)
			return ;
		i = open(exit, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		ft_putstr_fd(tmp, i);
	}
}
