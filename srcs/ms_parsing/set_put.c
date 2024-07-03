/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 05:37:13 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/19 16:45:15 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_put(t_put **put, t_params **para)
{
	t_put		*head_put;
	t_params	*head_para;
	int			i;

	head_para = *para;
	head_put = *put;
	if (head_put->input == NULL)
		head_put->input = NULL;
	if (head_put->output == NULL)
		head_put->output = NULL;
	i = 0;
	while (head_para->com[i] != NULL && head_para->com[i + 1] != NULL)
	{
		if (head_para->com[i][0] == '>')
			head_put->output = ft_strdup(head_para->com[i + 1]);
		else if (head_para->com[i][0] == '<' && head_para->com[i][1] == '\0')
			head_put->input = ft_strdup(head_para->com[i + 1]);
		i++;
	}
}

void	set_enum(t_params **para)
{
	t_params	*head;
	int			i;

	head = *para;
	i = 0;
	while (head->com[i] != NULL)
	{
		if (head->com[i][0] == '<')
		{
			if (head->com[i][1] == '<')
				head->inp_red = entre2;
			else if (head->com[i][1] == '\0')
				head->inp_red = entre1;
		}
		if (head->com[i][0] == '>')
		{
			if (head->com[i][1] == '>')
				head->out_red = sortie2;
			else if (head->com[i][1] == '\0')
				head->out_red = sortie1;
		}
		i++;
	}
}
