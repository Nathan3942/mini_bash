/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 04:04:52 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/03 17:01:30 by njeanbou         ###   ########.fr       */
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

char	*heredoc(char *exit)
{
	char	*doctmp;
	char	*res;
	char	*doc;

	doctmp = NULL;
	while (1)
	{
		doc = readline("heredoc> ");
		if (ft_strstr(doc, exit) == doc && ft_strlen(doc) == ft_strlen(exit))
		{
			res = ft_strdup_nl(doctmp);
			free(doctmp);
			break ;
		}
		doctmp = ft_strjoin_c(doctmp, doc, '\n');

	}
	return (res);
}

void	ft_doc(t_params **para)
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
		tmp = heredoc(exit);
		i = open(exit, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		ft_putstr_fd(tmp, i);
		// if (tmp != NULL)
		// 	head->com[--i] = tmp;
		// else
		// 	head->com[--i] = NULL;
	}
}
